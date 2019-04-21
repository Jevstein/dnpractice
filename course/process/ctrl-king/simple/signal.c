
#include <stdio.h>
#include <unistd.h>
#include <signal.h>


void sig_action(int signo) {
	if (signo == SIGINT) {
		printf("SIGINT\n");
		exit(1);
	}
	if (signo == SIGUSR1) {
		printf("SIGUSR1\n");
	}
}

void alarm_handler(int signo) {
	printf("alarm_handler\n");
}

int main(int argc, char **argv) {

	if (signal(SIGINT, sig_action) == SIG_ERR)
		printf("SIGINT");

	if (signal(SIGUSR1, sig_action) == SIG_ERR)
		printf("SIGUSR1");

	if (signal(SIGALRM, alarm_handler) == SIG_ERR)
		printf("SIGALRM");

	alarm(5);

	for ( ; ; ) 
		pause();

	return 0;
}
