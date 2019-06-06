
//network
//tfs, fastdsf, gfs, heystack, ceph


//storage
//ext4, ext3, nfs, fat32, 


//filesystem api
//fuse
//app --> main


///home/wangbojing/share/fuse/fuse-3.0.0/Makefile


#define FUSE_USE_VERSION	30

#include <fuse.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/uio.h>
#include <sys/ioctl.h>


static size_t sample_size;  //current buffer size
static void* sample_buf;    //buffer pointer

#define SAMPLE_NAME 	"sample"
#define FLAME_NAME 		"flame"


enum {
	SAMPLE_NONE,
	SAMPLE_ROOT, //"/"
	SAMPLE_FILE, //
};

static int sample_file_type(const char *path) {

	if (strcmp(path, "/") == 0) {
		return SAMPLE_ROOT;
	}
	if (strcmp(path, "/"SAMPLE_NAME) == 0) {
		return SAMPLE_FILE;
	}
	if (strcmp(path, "/"FLAME_NAME) == 0) {
		return SAMPLE_FILE;
	}
	
	return SAMPLE_NONE;
}

static sample_resize(size_t new_size) {

	if (new_size == sample_size) return 0;

	void *new_buf = realloc(sample_buf, new_size);
	if (!new_buf) {
		return -ENOMEM;
	}

	if (new_size > sample_size) {
		memset(new_buf + sample_size, 0, new_size - sample_size);
	}

	sample_buf = new_buf;
	sample_size = new_size;

	return 0;
}

static int sample_expand(size_t new_size) {

	if (new_size > sample_size) { 
		return sample_resize(new_size);
	}
	return 0;
}



static int sample_open(const char *path, struct fuse_file_info *fi) {

	if (sample_file_type(path) != SAMPLE_NONE) {
		return 0;
	}

	return -ENOENT;
	
}


static int sample_do_read(char *buf, size_t size, off_t offset) {

	if (offset >= sample_size) return 0;

	if (size > sample_size-offset) {
		size = sample_size-offset;
	}
	memcpy(buf, sample_buf+offset, size);

	fprintf(stderr, "sample_do_read: %s\n", buf);

	return size;
}

static int sample_read(const char *path, char *buf, size_t size, 
	off_t offset, struct fuse_file_info *fi) {

	if (sample_file_type(path) != SAMPLE_FILE) {
		return -EINVAL;
	}

	fprintf(stderr, "sample_read\n");
	
	return sample_do_read(buf, size, offset);
}

static int sample_do_write(const char *buf, size_t size, off_t offset) {

	if (sample_expand(offset+size)) {
		return -ENOMEM;
	}

	printf("sample_do_write: %s\n", buf);
	
	memcpy(sample_buf+offset, buf, size);

	return size;
}

static int sample_write(const char *path, const char *buf, size_t size,
	off_t offset, struct fuse_file_info *fi) {

	if (sample_file_type(path) != SAMPLE_FILE) {
		return -EINVAL;
	}
	
	return sample_do_write(buf, size, offset);
}


static int sample_getattr(const char *path, struct stat *stbuf, 
	struct fuse_file_info *fi) {

	stbuf->st_uid = getuid();
	stbuf->st_gid = getgid();

	stbuf->st_atime = stbuf->st_mtime = time(NULL);

	printf("sample_getattr\n");

	switch (sample_file_type(path)) {

		case SAMPLE_ROOT: {

			stbuf->st_mode = S_IFDIR | 0755;
			stbuf->st_nlink = 2;  //

			break;
		}

		case SAMPLE_FILE: {

			stbuf->st_mode = S_IFREG | 0644;
			stbuf->st_nlink = 1; // 
			stbuf->st_size = sample_size;
			
			break;
		}

		case SAMPLE_NONE: {
	
			return -ENOENT;
		}	

	}

	return 0;
}

static int sample_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset,
			struct fuse_file_info *fi, enum fuse_readdir_flags flags) {

	if (sample_file_type(path) != SAMPLE_ROOT) {
		return -ENOENT;
	}

	filler(buf, ".", NULL, 0, 0);
	filler(buf, "..", NULL, 0, 0);
	filler(buf, SAMPLE_NAME, NULL, 0, 0);
	filler(buf, FLAME_NAME, NULL, 0, 0);

	return 0;
}

//rwx   -->  read , write, exe
//				4		2 		1
// chmod 777 a.
static struct fuse_operations sample_ops = {

	.open = sample_open, 
	.getattr = sample_getattr,
#if 1
	.read = sample_read,
#endif
	.write = sample_write,
	.readdir = sample_readdir,
};


int main(int argc, char *argv[]) {
	return fuse_main(argc, argv, &sample_ops, NULL);
}




