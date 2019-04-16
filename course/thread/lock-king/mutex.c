

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

pthread_mutex_t mutex;


//cmpxchg
int CAS(int *addr, int _old, int _new) {

	int prev;

	__asm__ volatile(
		"lock; cmxchg %1, %2;"
		: "=a" (prev);
		: "r" (_new), "m" (*addr), "0"(_old)
		: "memory"
	);

	return prev;
}




int fetch_add(int *value, int add) {

	int old;

	__asm__ volatile (
		"lock; xsubl %2, %1;"  //asm 
		: "=a" (old) //output
		: "m" (*value), "a" (add) //input
		: "cc", "memory"
	);

	return old;
}


void *thread_proc(void *arg) {

	int *count = (int *)arg;
	int i = 0;

	while (i++ < 100000) {
#if 0
		pthread_mutex_lock(&mutex); //
		(*count) ++; //
		pthread_mutex_unlock(&mutex); //
#else

		fetch_add(count, 1); //a

#endif
		usleep(1);
	}

}



#define THREADS				10

int main() {

	int i = 0;
	pthread_t thread_id[THREADS];
	int count = 0;

	pthread_mutex_init(&mutex, NULL);

	for (i = 0;i < THREADS;i ++) {
		pthread_create(&thread_id[i], NULL, thread_proc, &count);
	}

	for (i = 0;i < 100;i ++) {
		printf("count --> %d\n", count);
		sleep(1);
	}
	
	for (i = 0;i < THREADS;i ++) {
		pthread_join(thread_id[i], NULL);
	}

}



