






#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char *argv[]) {

	int fd = open("hello", O_CREAT|O_RDWR|O_TRUNC);
	if (fd < 0) {
		printf("Open Error!!\n");
		return 0;
	}

	int nfd = dup(STDIN_FILENO);
	if (nfd < 0) {
		printf("Error\n");
		return 0;
	}

	char buf[1000];
	int n;

	while ((n = read(nfd, buf, 1000)) > 0) {
		if (write(fd, buf, n) != n) {
			printf("Write Error!!\n");
			return 0;
		}
	}

	return 0;

} 


