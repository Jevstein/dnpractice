

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>

pthread_rwlock_t rwlock;

#define WORK_SIZE		1024

char work_area[WORK_SIZE];
int time_to_exit;

void *thread_function_read_1(void *arg) {

	printf("thread read one try to get lock\n");

	pthread_rwlock_rdlock(&rwlock);

	while (strncmp("end", work_area, 3) != 0) {

		printf("the characters is %s", work_area);
		pthread_rwlock_unlock(&rwlock);
		sleep(2);
		pthread_rwlock_rdlock(&rwlock);

		while (work_area[0] == '\0') {
			pthread_rwlock_unlock(&rwlock);
			sleep(2);
			pthread_rwlock_rdlock(&rwlock);
		}
	}

	pthread_rwlock_unlock(&rwlock);

	time_to_exit = 1;
	//pthread_exit(0);

}

void *thread_function_read_2(void *arg) {

	printf("thread read two try to get lock\n");

	pthread_rwlock_rdlock(&rwlock);

	while (strncmp("end", work_area, 3) != 0) {

		printf("the characters is %s", work_area);
		pthread_rwlock_unlock(&rwlock);
		sleep(5);
		pthread_rwlock_rdlock(&rwlock);

		while (work_area[0] == '\0') {
			pthread_rwlock_unlock(&rwlock);
			sleep(5);
			pthread_rwlock_rdlock(&rwlock);
		}
	}

	pthread_rwlock_unlock(&rwlock);

	time_to_exit = 1;
	//pthread_exit(0);

}

void *thread_function_write_1(void *arg) {

	printf("thread write one try to get lock\n");

	while (!time_to_exit) {
		pthread_rwlock_wrlock(&rwlock);
		printf("this is write thread one.\nInput some text. Enter 'end' to finish\n");

		fgets(work_area, WORK_SIZE, stdin);
		pthread_rwlock_unlock(&rwlock);

		sleep(15);
	}

	pthread_rwlock_unlock(&rwlock);
	//pthread_exit(0);
	
}


void *thread_function_write_2(void *arg) {

	sleep(10);

	while (!time_to_exit) {

		pthread_rwlock_wrlock(&rwlock);
		printf("this is write thread two.\nInput some text. Enter 'end' to finish\n");

		fgets(work_area, WORK_SIZE, stdin);

		pthread_rwlock_unlock(&rwlock);
		sleep(20);
		
	}

	pthread_rwlock_unlock(&rwlock);
	//pthread_exit(0);
	
}

typedef void* (*thread_proc)(void *arg);
#define THREAD_PROC_SIZE		4

int main(int argc, char *argv[]) {

	pthread_t thread_id[THREAD_PROC_SIZE] = {0};

	thread_proc proc[THREAD_PROC_SIZE] = {
		thread_function_read_1,
		thread_function_read_2,
		thread_function_write_1,
		thread_function_write_2
	};

	int i = 0;
	for (i = 0;i < THREAD_PROC_SIZE;i ++) {
		pthread_create(&thread_id[i], NULL, proc[i], NULL);
	}
	for (i = 0;i < THREAD_PROC_SIZE;i ++) {
		pthread_join(thread_id[i], NULL);
	}
}


