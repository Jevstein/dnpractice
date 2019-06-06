
/*
 gcc -Wall sample_fioc.c -I /usr/local/include/fuse3/ -L /usr/local/lib/ -lfuse3 -o sample_fioc
 */

#define FUSE_USE_VERSION		30

#include <fuse.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/uio.h>
#include <sys/ioctl.h>

#define ENABLE_READ		0

enum {
	FIOC_GET_SIZE = _IOR('E', 0, size_t),
	FIOC_SET_SIZE = _IOW('E', 1, size_t),

	FIOC_READ = _IO('E', 2),
	FIOC_WRITE = _IO('E', 3),
	
};

struct fioc_rw_arg {
	off_t offset;
	void *buf;
	size_t size;
	size_t prev_size;
	size_t new_size;
};


#define FIOC_NAME		"fioc"

static size_t fioc_size;
static void *fioc_buf;

enum {
	FIOC_NONE,
	FIOC_ROOT,
	FIOC_FILE,
};

static int fioc_resize(size_t new_size) {

	void *new_buf;

	if (new_size == fioc_size) return 0;

	new_buf = realloc(fioc_buf, new_size);
	if (!new_buf) {
		return -ENOMEM;
	}

	if (new_size > fioc_size) {
		memset(new_buf + fioc_size, 0, new_size - fioc_size);
	}

	fioc_buf = new_buf;
	fioc_size = new_size;

	return 0;
}

static int fioc_expand(size_t new_size) {
	if (new_size > fioc_size) {
		return fioc_resize(new_size);
	}
	return 0;
}

static int fioc_file_type(const char *path) {
	if (strcmp(path, "/") == 0) {
		return FIOC_ROOT;
	}
	if (strcmp(path, "/" FIOC_NAME) == 0) {
		return FIOC_FILE;
	}
	return FIOC_NONE;
}

static int fioc_open(const char *path, struct fuse_file_info *fi) {

	if (fioc_file_type(path) != FIOC_NONE) {
		return 0;
	}
	return -ENOENT;
}
#if ENABLE_READ
static int fioc_do_read(char *buf, size_t size, off_t offset) {

	if (offset >= fioc_size) return 0;

	if (size > fioc_size - offset) {
		size = fioc_size - offset;
	}
	memcpy(buf, fioc_buf + offset, size);

	return size;
}

static int fioc_read(const char *path, char *buf, size_t size,
		     off_t offset, struct fuse_file_info *fi) {

	if (fioc_file_type(path) != FIOC_FILE) {
		return -EINVAL;
	}
	return fioc_do_read(buf, size, offset);
}
#endif

static int fioc_do_write(const char *buf, size_t size, off_t offset) {
	if (fioc_expand(offset + size)) {
		return -ENOMEM;
	}
	memcpy(fioc_buf + offset, buf, size);
	return size;
}

static int fioc_write(const char *path, const char *buf, size_t size,
	off_t offset, struct fuse_file_info *fi) {

	if (fioc_file_type(path) != FIOC_FILE) {
		return -EINVAL;
	}
	return fioc_do_write(buf, size, offset);

}

static int fioc_ioctl(const char *path, int cmd, void *arg,
	struct fuse_file_info *fi, unsigned int flags, void *data) {

	if (fioc_file_type(path) != FIOC_FILE) {
		return -EINVAL;
	}

	if (flags & FUSE_IOCTL_COMPAT) {
		return -ENOSYS;
	}

	switch (cmd) {
		
		case FIOC_GET_SIZE: {
			*(size_t*)data = fioc_size;
			return 0;
		}
		case FIOC_SET_SIZE: {
			fioc_resize(*(size_t*)data);
			return 0;
		}
	}

	return -EINVAL;
}

static int fioc_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
	off_t offset, struct fuse_file_info *fi, enum fuse_readdir_flags flags) {

	if (fioc_file_type(path) != FIOC_ROOT) {
		return -ENOENT;
	}

	filler(buf, ".", NULL, 0, 0);
	filler(buf, "..", NULL, 0, 0);
	filler(buf, FIOC_NAME, NULL, 0, 0);

	return 0;
}

static int fioc_getattr(const char *path, struct stat *stbuf,
	struct fuse_file_info *fi) {

	stbuf->st_uid = getuid();
	stbuf->st_gid = getgid();
	stbuf->st_atime = stbuf->st_mtime = time(NULL);

	switch (fioc_file_type(path)) {
		case FIOC_ROOT:
			stbuf->st_mode = S_IFDIR | 0755;
			stbuf->st_nlink = 2;
			break;
		case FIOC_FILE:
			stbuf->st_mode = S_IFREG | 0644;
			stbuf->st_nlink = 1;
			stbuf->st_size = fioc_size;
			break;
		case FIOC_NONE:
			return -ENOENT;
	}
	return 0;
}


static struct fuse_operations fioc_oper = {

	.open = fioc_open,
#if ENABLE_READ
	.read = fioc_read,
#endif
	.write = fioc_write,
	.ioctl = fioc_ioctl,

	.readdir = fioc_readdir,
	.getattr = fioc_getattr,
};

int main(int argc, char *argv[]) {
	return fuse_main(argc, argv, &fioc_oper, NULL);
}


