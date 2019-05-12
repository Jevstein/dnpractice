


#include <linux/module.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <linux/slab.h>
#include <linux/poll.h>


#ifndef NTYCHANNEL_MAJOR
#define NTYCHANNEL_MAJOR	96
#endif

#ifndef NTYCHANNEL_NR_DEVS
#define NTYCHANNEL_NR_DEVS	2
#endif

#ifndef NTYCHANNEL_SIZE
#define NTYCHANNEL_SIZE		4096
#endif

#define ENABLE_POLL		1

struct ntychannel {
	char *data;
	unsigned long size;
#if ENABLE_POLL
	wait_queue_head_t inq;
#endif
};

static int channel_major = NTYCHANNEL_MAJOR;
module_param(channel_major, int, S_IRUGO);

struct ntychannel *channel_devp;
struct cdev cdev;

char have_data = 0;


int ntychannel_open(struct inode *inode, struct file *filp) {

	struct ntychannel *channel;

	int num = MINOR(inode->i_rdev);
	if (num >= NTYCHANNEL_NR_DEVS)
		return -ENODEV;

	channel = &channel_devp[num];

	filp->private_data = channel;

	return 0;
}

int ntychannel_release(struct inode *inode, struct file *filp) {
	return 0;
}

ssize_t ntychannel_read(struct file *filp, char __user *buffer, size_t size, loff_t *ppos) {
	unsigned long p = *ppos;
	unsigned int count = size;

	int ret = 0;
	struct ntychannel *channel = filp->private_data;
	if (p >= NTYCHANNEL_SIZE) {
		return 0;
	}

	if (count > NTYCHANNEL_SIZE - p) {
		count = NTYCHANNEL_SIZE - p;
	}

#if ENABLE_POLL
	while (!have_data) {
		if (filp->f_flags & O_NONBLOCK) return -EAGAIN;

		wait_event_interruptible(channel->inq, have_data);
	}
#endif

	if (copy_to_user(buffer, (void*)(channel->data+p), count)) {
		ret = -EFAULT;
	} else {
		ret = strlen(buffer);
		channel->size -= ret;
		
		printk(KERN_INFO "read %d byte(s) from %ld\n", ret, p);
	}

	have_data = 0;

	return ret;
}

ssize_t ntychannel_write(struct file *filp, const char __user *buffer, size_t size, loff_t *ppos) {

	int ret = 0;
	unsigned long p = *ppos;
	unsigned int count = size;

	struct ntychannel *channel = filp->private_data;
	if (p >= NTYCHANNEL_SIZE) {
		return 0;
	}

	if (count > NTYCHANNEL_SIZE - p) {
		count = NTYCHANNEL_SIZE - p;
	}

	if (copy_from_user(channel->data+p, buffer, count)) {
		return -EFAULT;
	} else {
		*ppos += count;
		ret = count;
		channel->size += count;

		*(channel->data+p + count) = '\0'; 

		printk(KERN_INFO "written %d byte(s) from %ld\n", count, p);
	}

#if ENABLE_POLL
	have_data = 1;
	wake_up(&channel->inq);
#endif

	return ret;
}

#if ENABLE_POLL
unsigned int ntychannel_poll(struct file *filp, struct poll_table_struct *wait) {
	
	struct ntychannel *channel = filp->private_data;
	unsigned int mask = 0;

	poll_wait(filp, &channel->inq, wait);

	if (have_data)
		mask |= (POLLIN | POLLRDNORM);

	return mask;
	
}
#endif

loff_t ntychannel_llseek(struct file *filp, loff_t offset, int whence) {
	loff_t newpos;

	switch (whence) {
		case 0: {
			newpos = offset;
			break;
		}
		case 1: {
			newpos = filp->f_pos + offset;
			break;
		}
		case 2: {
			newpos = NTYCHANNEL_SIZE - 1 + offset;
			break;
		}
		default: {
			return -EINVAL;
		}
	}

	if (newpos < 0 || newpos > NTYCHANNEL_SIZE) {
		return -EINVAL;
	}

	filp->f_pos = newpos;

	return newpos;
}

int ntychannel_mmap(struct file *filp, struct vm_area_struct *vma) {
	struct ntychannel *channel = filp->private_data;

	vma->vm_flags |= VM_IO;
	vma->vm_flags |= (VM_DONTEXPAND | VM_DONTDUMP);

	if (remap_pfn_range(vma, vma->vm_start, virt_to_phys(channel->data) >> PAGE_SHIFT, 
		vma->vm_end-vma->vm_start, vma->vm_page_prot)) {
		return -EAGAIN;
	}
	
	return 0;
}

static const struct file_operations ntychannel_fops = {
	.owner = THIS_MODULE,
	.llseek = ntychannel_llseek,
	.read = ntychannel_read,
	.write = ntychannel_write,
	.open = ntychannel_open,
	.release = ntychannel_release,
	.poll = ntychannel_poll,
	.mmap = ntychannel_mmap,
};

static int ntychannel_init(void) {

	int result;
	int i;

	dev_t devno = MKDEV(channel_major, 0);
	if (channel_major) {
		result = register_chrdev_region(devno, NTYCHANNEL_NR_DEVS, "ntychannel");
	} else {
		result = alloc_chrdev_region(&devno, 0, NTYCHANNEL_NR_DEVS, "ntychannel");
		channel_major = MAJOR(devno);
	}

	if (result < 0) return result;

	cdev_init(&cdev, &ntychannel_fops);
	cdev.owner = THIS_MODULE;

	cdev_add(&cdev, MKDEV(channel_major, 0), NTYCHANNEL_NR_DEVS);

	channel_devp = kmalloc(NTYCHANNEL_NR_DEVS * sizeof(struct ntychannel), GFP_KERNEL);
	if (!channel_devp) {
		result = -ENOMEM;
		goto fail_malloc;
	}
	memset(channel_devp, 0, sizeof(struct ntychannel));

	for (i = 0;i < NTYCHANNEL_NR_DEVS;i ++) {
		channel_devp[i].size = NTYCHANNEL_SIZE;
		channel_devp[i].data = kmalloc(NTYCHANNEL_SIZE, GFP_KERNEL);
		memset(channel_devp[i].data, 0, NTYCHANNEL_SIZE);
#if ENABLE_POLL
		init_waitqueue_head(&(channel_devp[i].inq));
#endif
	}

	printk(KERN_INFO "ntychannel_init");

	return 0;

fail_malloc:
	unregister_chrdev_region(devno, 1);

	return result;
}


static void ntychannel_exit(void) {

	printk(KERN_INFO "ntychannel_exit");
	
	cdev_del(&cdev);
	kfree(channel_devp);

	unregister_chrdev_region(MKDEV(channel_major, 0), 2);
}


MODULE_AUTHOR("WangBoJing");
MODULE_LICENSE("GPL");

module_init(ntychannel_init);
module_exit(ntychannel_exit);


