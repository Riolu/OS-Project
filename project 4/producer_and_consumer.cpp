#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>

typedef int buffer_item;
#define BUFFER_SIZE 5
#define NUM 100 //maximum num of producer_threads or consumer_threads
buffer_item buffer[BUFFER_SIZE]; //the shared buffer

sem_t empty, full;
sem_t mutex;
int in = 0, out = 0; //in = first empty buffer, out = first full buffer
int pOrder[NUM], cOrder[NUM];

void *producer(void *param)
{
    buffer_item ran;
    int id = *(int *) param;

    while(1)
    {
        sleep(rand() % 5);
        ran = rand() % 1000;
		
		sem_wait(&empty);
		sem_wait(&mutex);
		
		buffer[in] = ran;
		printf("Producer %d has produced %d\tto buffer[%d] \n", id, ran, in); 
		in = (in + 1) % BUFFER_SIZE;
		
		sem_post(&mutex);
		sem_post(&full);
          
    }
    return NULL;
    
}

void *consumer(void *param)
{
    buffer_item ran;
	int id = *(int *) param;

    while(1)
    {
        sleep(rand() % 5);

		sem_wait(&full);
		sem_wait(&mutex);
		
		ran = buffer[out];
		printf("Consumer %d has consumed %d\tin buffer[%d] \n", id, ran, out);
		out = (out + 1) % BUFFER_SIZE;
		
		sem_post(&mutex);
		sem_post(&empty);
		
    }
    return NULL;
    
}

void callError()
{
	perror("create thread error!\n");
	exit(0);
}

int main(int argc, char *argv[])
{
    int pNum, cNum, sleepTime, i, ret;
    pthread_t p_thread[NUM];
    pthread_t c_thread[NUM];
	
    scanf("%d",&sleepTime);
    scanf("%d",&pNum);
    scanf("%d",&cNum);


    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
	sem_init(&mutex, 0, 1);
    
    

    for(i = 0; i < pNum; ++i)
    {
		pOrder[i] = 1 + i;
        ret = pthread_create(&p_thread[i], NULL, producer, &pOrder[i]);
		if(ret != 0) callError();
    }
    

    for(i = 0; i < cNum; ++i)
    {
		cOrder[i] = 1 + i;
        ret = pthread_create(&c_thread[i], NULL, consumer, &cOrder[i]);
		if(ret != 0) callError();
    }
    
    sleep(sleepTime);
    return 0;
    
}
