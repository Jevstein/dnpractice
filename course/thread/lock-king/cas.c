

#include <stdio.h>


// unsigned long cmpxchg(void *addr, unsigned long _old, unsigned long _new) {
// 	int *a = addr;

// 	if (*a == _old) {
// 		*a = _new;
// 	}

// 	return _old;
// }

unsigned long cmpxchg(void *addr, unsigned long _old, unsigned long _new) {
	unsigned long prev;
	volatile unsigned int *_ptr = (volatile unsigned int *)addr;

	__asm__ volatile (
		"lock; cmpxchg %1, %2"	
		: "=a" (prev)
		: "r" (_new), "m" (*_ptr), "0" (_old)
		: "memory"
	);

	return prev;
}

int main() {
	int data = 0;
	cmpxchg(&data, data, data+1);
}


