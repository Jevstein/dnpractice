


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/fcntl.h>


int main(int argc, char *argv[]) {

	if (argc < 2) {
		fprintf(stderr, "%s", "parameter error\n");
		return -1;
	}

	int fd = open(argv[1], O_RDWR);
	if (fd < 0) {
		perror("open");
		return 1;
	}

	char *text = "king vip\n";
	write(fd, text, strlen(text));

	close(fd);

	return 0;

}



