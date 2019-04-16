

#include <stdio.h>
#include <sys/timeb.h>

long long getSystemTime() {
	struct timeb t;
	ftime(&t);

	return (1000 * t.time + t.millitm);
}

#define TIME 	10000000

int main() {
	volatile int i = 0;
	int a = 0;

	long long start = 0, end = 0;

	start = getSystemTime();
	for (i = 0;i < TIME;i ++);
		end = getSystemTime();

	printf("volatile : %lld ms\n", end-start);

	start = getSystemTime();
	for (a = 0;a < TIME;a ++);
		end = getSystemTime();

	printf("generic : %lld ms\n", end-start);

	return 0;
}



