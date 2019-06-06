

#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
//#include "ioctl.h"

const char *usage =
"Usage: fioclient FIOC_FILE [size]\n"
"\n"
"Get size if <size> is omitted, set size otherwise\n"
"\n";

enum {
	FIOC_GET_SIZE = _IOR('E', 0, size_t),
	FIOC_SET_SIZE = _IOW('E', 1, size_t),

	FIOC_READ = _IO('E', 2),
	FIOC_WRITE = _IO('E', 3),
	
};


int main(int argc, char *argv[]) {

	size_t size;
	int fd;

	if (argc < 2) {

		fprintf(stderr, "%s", usage);
		return 1;

	}

	fd = open(argv[1], O_RDWR);
	if (fd < 0) {
		perror("open");
		return 1;
	}

	if (argc == 2) {

		if (ioctl(fd, FIOC_GET_SIZE, &size)) {
			perror("ioctl");
			return 1;
		} 
		printf("%zu\n", size);
	} else {

		size = strtoul(argv[2], NULL, 0);
		if (ioctl(fd, FIOC_SET_SIZE, &size)) {
			perror("ioctl");
			return 1;
		}
	}

	char buffer[128] = {0};
	read(fd, buffer, 128);
	printf("%s --> %s\n", argv[1], buffer);

	return 0;

}


