#include <pthread.h> 
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/* this data is shared by the thread(s) */

int threads;			// number of products to iterate
unsigned long long iterations;  // number of threads to use
double * pi_arr;		// pi product

void * runner(void * param); 	// the thread

int main(int argc, char * argv[]) 
{
        if (argc != 3) 
	{
            fprintf(stderr, "usage: a.out <iterations> <threads>\n");
            return -1;
        }
        if (atoi(argv[1]) < 0 || atoi(argv[2]) < 0) 
	{
            fprintf(stderr, "Arguments must be non-negative\n ");
            return -1;
        }

	iterations = atoi(argv[1]); 	
	threads = atoi(argv[2]);	

	pi_arr = (double*) malloc(threads * sizeof (double)); // create array to store pi values	
	for (int m = 0; m < threads; m++) {
		pthread_t tid; // create thread identifier
		pthread_attr_t attr;	// create thread attributes
		pthread_attr_init(&attr);	// initialize attributes to default
		pthread_create(&tid, &attr, runner, (void *) m); // create thread
		pthread_join(tid, NULL); // join thread
	}

	double pi = 0;
	// add all sums in array
	for (int n = 0; n < threads; n++) {
		pi = pi + pi_arr[n];
	}
	pi = pi * 4;
	printf("iterations: %llu, threads: %d\n", iterations, threads);
	printf("value for pi: %.15f\n", pi);
}

/**
 * The thread will begin control in this function
 */
void * runner(void * param)
{
	int thread = (int) param;
	pi_arr[thread] = 0;

	// set lower bound and upper bound for sum
	for (int i = (int) thread*(iterations/threads); i < (int) (thread + 1)*(iterations/threads); i++)
	{
	        double product = (double) pow(-1, i) / (2*i+1); // formula for i'th element in pi_arr series
		pi_arr[thread] = pi_arr[thread] + product;
	}

        pthread_exit(0);
}	
