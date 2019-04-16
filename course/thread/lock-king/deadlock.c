

#include <stdio.h>
#include <pthread.h>


pthread_mutex_t mutex_one, mutex_two, mutex;
pthread_cond_t cond;


void *thread_routine_one(void *arg) {

	pthread_mutex_lock(&mutex);
	pthread_cond_wait(&cond, &mutex);
	pthread_mutex_unlock(&mutex);

	pthread_mutex_lock(&mutex_one);
	pthread_mutex_lock(&mutex_two);

	sleep(1);

	pthread_mutex_unlock(&mutex_two);
	pthread_mutex_unlock(&mutex_one);

	return NULL;
	
}


void *thread_routine_two(void *arg) {

	pthread_mutex_lock(&mutex_two);
	pthread_cond_signal(&cond);
	sleep(1);

	pthread_mutex_lock(&mutex_one);

	pthread_mutex_unlock(&mutex_one);
	pthread_mutex_unlock(&mutex_two);

	return NULL;
}

int main(void) {

	pthread_t pthread_one, pthread_two;

	pthread_mutex_init(&mutex_one, NULL);
	pthread_mutex_init(&mutex_two, NULL);
	pthread_mutex_init(&mutex, NULL);

	pthread_cond_init(&cond, NULL);

	pthread_create(&pthread_one, NULL, thread_routine_one, NULL);
	pthread_create(&pthread_two, NULL, thread_routine_two, NULL);

	pthread_join(pthread_one, NULL);
	pthread_join(pthread_two, NULL);

}


