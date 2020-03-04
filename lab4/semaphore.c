#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 20

int in = 0, out = 0, count = 0;
int buffer [BUFFER_SIZE];

pthread_t tid;
sem_t sem;
sem_t full;
sem_t empty;

void insert(int item){
   sem_wait(&empty);
   sem_wait(&sem);
   buffer[in] = item;
   in = (in + 1) % BUFFER_SIZE;
   sleep(1);   
   sem_post(&sem);
   sem_post(&full);
}

int remove_item(){
   int item;
   sem_wait(&full);
   sem_wait(&sem);
   item = buffer[out];
   out = (out + 1) % BUFFER_SIZE;
   sleep(1);    
   sem_post(&sem);
   sem_post(&empty);
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
    sem_init(&sem, 0, 1);
    sem_init(&full, 0 , 0);
    sem_init(&empty, 0, BUFFER_SIZE);

    int producers = atoi(argv[1]);
    int consumers = atoi(argv[2]);
    pthread_t tid_producers[producers];
    pthread_t tid_consumers[consumers];
    
    int i;

    for (i = 0; i < producers; i++)
       pthread_create(&tid_producers[i], NULL, producer,NULL);

    for (i = 0; i < consumers; i++)
       pthread_create(&tid_consumers[i], NULL, consumer, NULL); 

    for (i = 0; i < producers; i++)
       pthread_join(tid_producers[i],NULL);

    for (i = 0; i < consumers; i++)
       pthread_join(tid_consumers[i],NULL);

    sem_destroy(&sem);
}
