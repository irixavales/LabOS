#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main ()
{
	if (fork() && !fork()) {
		if (fork() || fork()) {
			fork();
		}
	}

	// this is to construct a process tree
	// printf("process id: %d, my parent is: %d\n", getpid(), getppid());
	printf("2 ");
	return 0;
}
