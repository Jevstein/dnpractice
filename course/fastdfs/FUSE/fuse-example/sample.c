/*

 gcc -Wall sample.c -I /usr/local/include/fuse3/ -L /usr/local/lib/ -lfuse3 -o sample

 */


//#include <config.h>

#include <fuse_lowlevel.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>

#define ENABLE_INODE5	1
#define ENABLE_BINARY	1

static const char *sample_str = "Hello Fuse's World\n";
static const char *sample_name = "sample";

#if ENABLE_INODE5
static const char *inode5_str = "http://www.ntytcp.com\n";
static const char *inode5_name = "frombyte";
#endif

#if ENABLE_BINARY
static const char *inode3_name = "frombyte.dir";
static const char *inode6_name = "inode6.img";
#endif

static int sample_stat(fuse_ino_t ino, struct stat *stbuf) {

	stbuf->st_ino = ino;
	switch (ino) {

		case 1:
			stbuf->st_mode = S_IFDIR | 0755;
			stbuf->st_nlink = 2;
			break;

		case 2:
			stbuf->st_mode = S_IFREG | 0444;
			stbuf->st_nlink = 1;
			stbuf->st_size = strlen(sample_str);
			break;
			
#if ENABLE_BINARY
		case 3:
			stbuf->st_mode = S_IFDIR | 0755;
			stbuf->st_nlink = 2;
			break;
#endif

#if ENABLE_INODE5
		case 5:
			stbuf->st_mode = S_IFREG | 0444;
			stbuf->st_nlink = 1;
			stbuf->st_size = strlen(inode5_str);
			break;
#endif

#if ENABLE_BINARY
		case 6:
			stbuf->st_mode = S_IFREG | 0444;
			stbuf->st_nlink = 1;
			stbuf->st_size = 1024 * 1024 * 1024;
			break;
#endif

		default:
			return -1;

	}

	return 0;

}


static void sample_getattr(fuse_req_t req, fuse_ino_t ino, struct fuse_file_info *fi) {
	struct stat stbuf;

	memset(&stbuf, 0, sizeof(stbuf));
	if (sample_stat(ino, &stbuf) == -1) {
		fuse_reply_err(req, ENOENT);
	} else {
		fuse_reply_attr(req, &stbuf, 1.0);
	}
}

static void sample_lookup(fuse_req_t req, fuse_ino_t parent, const char *name) {

	struct fuse_entry_param e;
#if (ENABLE_INODE5==0)
	if (parent != 1 || strcmp(name, sample_name) != 0) {
		
		fuse_reply_err(req, ENOENT);
		
	} else {

		memset(&e, 0, sizeof(e));
		e.ino = 2;
		e.attr_timeout = 1.0;
		e.entry_timeout = 1.0;
		sample_stat(e.ino, &e.attr);

		fuse_reply_entry(req, &e);
	}
#elif (ENABLE_INODE5==1)

	if (parent != 1) {
		fuse_reply_err(req, ENOENT);
	} else if (strcmp(name, sample_name) == 0) {
		memset(&e, 0, sizeof(e));
		e.ino = 2;
		e.attr_timeout = 1.0;
		e.entry_timeout = 1.0;
		
		sample_stat(e.ino, &e.attr);
		fuse_reply_entry(req, &e);
	} else if (strcmp(name, inode5_name) == 0) {

		memset(&e, 0, sizeof(e));
		e.ino = 5;
		e.attr_timeout = 1.0;
		e.entry_timeout = 1.0;

		sample_stat(e.ino, &e.attr);
		fuse_reply_entry(req, &e);
		
	} else {

		fuse_reply_err(req, ENOENT);
		
	}

#elif (ENABLE_BINARY==1) 

	switch (parent) {

		case 1:
			if (strcmp(name, sample_name) == 0) {
				memset(&e, 0, sizeof(e));
				e.ino = 2;
				e.attr_timeout = 1.0;
				e.entry_timeout = 1.0;
				
				sample_stat(e.ino, &e.attr);
				fuse_reply_entry(req, &e);
				
			} else if (strcmp(name, inode3_name) == 0) {

				memset(&e, 0, sizeof(e));
				e.ino = 3;
				e.attr_timeout = 1.0;
				e.entry_timeout = 1.0;

				sample_stat(e.ino, &e.attr);
				fuse_reply_entry(req, &e);
				
			} else {

				fuse_reply_err(req, ENOENT);
			
			}
			
			break;
			
		case 3:

			if (strcmp(name, inode5_name) == 0) {
				memset(&e, 0, sizeof(e));
				e.ino = 5;
				e.attr_timeout = 1.0;
				e.entry_timeout = 1.0;

				sample_stat(e.ino, &e.attr);
				fuse_reply_entry(req, &e);
				
			} else if (strcmp(name, inode6_name) == 0) {
			
				memset(&e, 0, sizeof(e));
				e.ino = 6;
				e.attr_timeout = 1.0;
				e.entry_timeout = 1.0;

				sample_stat(e.ino, &e.attr);
				fuse_reply_entry(req, &e);

			} else {

				fuse_reply_err(req, ENOENT);
				break;
			}
			
			break;
			
		default:
			fuse_reply_err(req, ENOENT);
			break;

	}

#endif
}


struct dirbuf {
	char *p;
	size_t size;
};

static void dirbuf_add(fuse_req_t req, struct dirbuf *b, 
	const char *name, fuse_ino_t ino) {

	struct stat stbuf;
	size_t oldsize = b->size;

	b->size += fuse_add_direntry(req, NULL, 0, name, NULL, 0);
	b->p = (char *)realloc(b->p, b->size);

	memset(&stbuf, 0, sizeof(stbuf));
	stbuf.st_ino = ino;

	fuse_add_direntry(req, b->p+oldsize, b->size-oldsize, name, &stbuf, b->size);

}

#define min(x, y) ((x) < (y) ? (x) : (y))

static int reply_buf_limited(fuse_req_t req, const char *buf, size_t bufsize,
	off_t off, size_t maxsize) {

	if (off < bufsize) {
		return fuse_reply_buf(req, buf+off, min(bufsize-off, maxsize));
	}

	return fuse_reply_buf(req, NULL, 0);

}


static void sample_readdir(fuse_req_t req, fuse_ino_t ino, size_t size,
	off_t off, struct fuse_file_info *fi) {

#if (ENABLE_BINARY==0)
	if (ino != 1) {

		fuse_reply_err(req, ENOTDIR);

	} else {

		struct dirbuf b;

		memset(&b, 0, sizeof(b));
		dirbuf_add(req, &b, ".", 1);
		dirbuf_add(req, &b, "..", 1);

		dirbuf_add(req, &b, sample_name, 2);
		dirbuf_add(req, &b, inode5_name, 5);

		reply_buf_limited(req, b.p, b.size, off, size);

		free(b.p);
	}

#else

	struct dirbuf b;

	switch (ino) {

		case 1:
			memset(&b, 0, sizeof(b));
			dirbuf_add(req, &b, ".", 1);
			dirbuf_add(req, &b, "..", 1);
			dirbuf_add(req, &b, sample_name, 2);
			dirbuf_add(req, &b, inode3_name, 3);

			reply_buf_limited(req, b.p, b.size, off, size);

			free(b.p);
			break;

		case 3:
			memset(&b, 0, sizeof(b));
			dirbuf_add(req, &b, ".", 1);
			dirbuf_add(req, &b, "..", 1);
			dirbuf_add(req, &b, inode5_name, 5);
			dirbuf_add(req, &b, inode6_name, 6);

			reply_buf_limited(req, b.p, b.size, off, size);

			free(b.p);
			break;

		default:
			fuse_reply_err(req, ENOTDIR);
			break;

	}

#endif
}


static void sample_open(fuse_req_t req, fuse_ino_t ino, 
	struct fuse_file_info *fi) {

#if 1 //ENABLE_BINARY	

	switch (ino) {
		case 2:
		case 5:
		case 6:
			if ((fi->flags & 3) != O_RDONLY)
				fuse_reply_err(req, EACCES);
			else
				fuse_reply_open(req, fi);
			break;

		default:
			fuse_reply_err(req, EISDIR);
			break;
	}
	
#else


#if (ENABLE_INODE5==0)
	if (ino != 2) {
#else
	if (ino != 2 && ino != 5) {
#endif
		fuse_reply_err(req, EISDIR);
	} else if ((fi->flags & 3) != O_RDONLY) {
		fuse_reply_err(req, EACCES);
	} else {
		fuse_reply_open(req, fi);
	}
	



#endif
}



static void sample_read(fuse_req_t req, fuse_ino_t ino, size_t size, 
	off_t off, struct fuse_file_info *fi) {
#if (ENABLE_INODE5 == 0)
	reply_buf_limited(req, sample_str, strlen(sample_str), off, size);
#else

	char *tbuf;

	switch (ino) {

		case 2:
			reply_buf_limited(req, sample_str, strlen(sample_str), off, size);
			break;
		case 5:
			reply_buf_limited(req, inode5_str, strlen(inode5_str), off, size);
			break;
#if ENABLE_BINARY
		case 6:
			tbuf = (char *)malloc(size);
			int i = 0;
			
			for (i = 0;i < size / sizeof(int);i ++) {
				((int*)tbuf)[i] = size;
			}

			fuse_reply_buf(req, tbuf, size);
			free(tbuf);
			
			break;
#endif
		default:
			;
	}

#endif
}

static struct fuse_lowlevel_ops sample_ops = {

	.lookup = sample_lookup,
	.getattr = sample_getattr,
	.readdir = sample_readdir,
	.open = sample_open,
	.read = sample_read,
	
};


int main(int argc, char *argv[]) {

	struct fuse_args args = FUSE_ARGS_INIT(argc, argv);
	struct fuse_session *se;
	struct fuse_cmdline_opts opts;

	int ret = 0;

	if (fuse_parse_cmdline(&args, &opts) != 0) {
		return 1;
	}

	if (opts.show_help) {
		fuse_cmdline_help();
		fuse_lowlevel_help();

		ret = 0;
		goto err_out1;
	} else if (opts.show_version) {

		printf("FUSE library version %s\n", fuse_pkgversion());
		fuse_lowlevel_version();
		ret = 0;
		goto err_out1;
	}

	se = fuse_session_new(&args, &sample_ops, sizeof(sample_ops), NULL);
	if (se == NULL) {
		goto err_out1;
	}

	if (fuse_set_signal_handlers(se) != 0) {
		goto err_out2;
	}

	if (fuse_session_mount(se, opts.mountpoint) != 0) {
		goto err_out3;
	}

	fuse_daemonize(opts.foreground);

	if (opts.singlethread) {
		ret = fuse_session_loop(se);
	} else {
		ret = fuse_session_loop_mt(se, opts.clone_fd);
	}
	fuse_session_unmount(se);

err_out3:
	fuse_remove_signal_handlers(se);

err_out2:
	fuse_session_destroy(se);

err_out1:
	free(opts.mountpoint);
	fuse_opt_free_args(&args);

	return ret ? 1 : 0;

}


