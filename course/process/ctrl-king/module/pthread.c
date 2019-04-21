


#include <stdio.h>
#include <pthread.h>

struct pair {
	int x;
	int y;
};

int total = 0;

void cleanup(void *arg) {
	printf("cleanup: %s\n", (char *)arg);
}

void *thread_proc(void *arg) {
#if 1
	pthread_cleanup_push(cleanup, "thread_proc handler\n");

	pthread_exit(0);

	pthread_cleanup_pop(0);
#else

	struct pair *p = (struct pair*)arg;
	total = p->x + p->y;
	
	return &total;
#endif

}

#if 0
	struct pair *p = (struct pair*)arg;
	total = p->x + p->y;
	
	return &total;
#else
#endif



int main() {

	struct pair p = {2, 3};

	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	pthread_t thread_id;
	int ret = pthread_create(&thread_id, &attr, thread_proc, &p);
	if (ret) {
		printf("pthread_create failed\n");
		return 0;
	}

	void *sum = 0;
	pthread_join(thread_id, &sum);  //5 //suiji  //0   //coredump
	///子线程不退出，join不返回
	//join ,子线程

	printf("sum : %d\n", *(int*)sum);
	
}







