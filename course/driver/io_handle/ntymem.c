


#ifndef NTYCHANNEL_MAJOR
#define NTYCHANNEL_MAJOR	96
#endif

#ifndef NTYCHANNEL_NR_DEVS
#define NTYCHANNEL_NR_DEVS	2
#endif

#ifndef NTYCHANNEL_SIZE
#define NTYCHANNEL_SIZE		4096
#endif

struct ntychannel {
	char *data;
	unsigned long size;
};

static int channel_major = NTYCHANNEL_MAJOR;
module_param(channel_major, int, S_IRUGO);

struct ntychannel *channel_devp;
struct cdev cdev;

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

ssize_t (*read) (struct file *, char __user *, size_t, loff_t *);


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

	//cdev_init(cdev, )

}



