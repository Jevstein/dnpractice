

#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {

	if (argc < 2) return -1;

	int fd;
	char *mmaped_mem, *p;

	int flength = 1024;
	void *start_addr = 0;

	fd = open(argv[1], O_RDWR | O_CREAT, S_IRUSR|S_IWUSR);
	flength = lseek(fd, 1, SEEK_END);

	write(fd, "\0", 1);
	lseek(fd, 0, SEEK_SET);

	mmaped_mem = mmap(start_addr, flength, PROT_READ, MAP_PRIVATE, fd, 0);
	printf("%s\n", mmaped_mem);

	close(fd);

	munmap(mmaped_mem, flength);
	
	return 0;
}



