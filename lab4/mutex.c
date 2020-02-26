#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 20

int in = 0, out = 0;
int buffer [BUFFER_SIZE];

pthread_t tid;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

void insert(int item){
   while ((in + 1) % BUFFER_SIZE == out);
   pthread_mutex_lock(&mutex1);
   buffer[in] = item;
   in = (in + 1) % BUFFER_SIZE;
   pthread_mutex_unlock(&mutex1);
   sleep(1); 
}

int remove_item(){
   int item;
   while (in == out);
   pthread_mutex_lock(&mutex1);
   item = buffer[out];
   out = (out + 1) % BUFFER_SIZE;
   pthread_mutex_unlock(&mutex1);
   sleep(1); 
   return item;
}

void * producer(void * param){
   int item;
   while(1){
      item = rand() % BUFFER_SIZE ;
      insert(item);
      printf("in: %d inserted: %d\n", in, item);
   }
}

void * consumer(void * param){
   int item;
   while(1){
   	item = remove_item();
   	printf("out: %d removed: %d\n", out, item);
   }
}

int main(int argc, char * argv[])
{
    int producers = atoi(argv[1]);
    int consumers = atoi(argv[2]);
    int i;

    for (i = 0; i < producers; i++)
       pthread_create(&tid, NULL, producer,NULL);

    for (i = 0; i < consumers; i++)
       pthread_create(&tid, NULL, consumer, NULL); 

    pthread_join(tid,NULL);
}
