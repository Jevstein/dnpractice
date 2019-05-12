


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>


#define BUFFER_LENGTH	128

int main() {

	int fd = open("/dev/ntychannel0", O_RDWR);
	if (fd < 0) return -1;
	
	char *buffer = (char *)malloc(BUFFER_LENGTH);
	memset(buffer, 0, BUFFER_LENGTH);

	char *start = mmap(NULL, BUFFER_LENGTH, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	strcpy(buffer, start);
	sleep(1);
	printf("buf 1 = %s\n", buffer);

	strcpy(start, "Buffer is not NULL!\n");

	memset(buffer, 0, BUFFER_LENGTH);
	strcpy(buffer, start);

	sleep(1);

	printf("buf 2 = %s\n", buffer);

	munmap(start, BUFFER_LENGTH);
	free(buffer);
	close(fd);

	return 0;
	
}


