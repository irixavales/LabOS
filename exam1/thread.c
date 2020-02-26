#include <stdio.h>
#include <pthread.h>

void * fcn (void * param);

int main () {
	pthread_t tid;
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	pthread_create(&tid, &attr, fcn, NULL);
	pthread_join(tid, NULL);

	return 0;
}

void * fcn (void * param) {
	printf("I am alive!");
}
