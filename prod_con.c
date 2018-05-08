#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>

sem_t empty,full,mutex1;
int buffer[6],out=0,in=0,item1=0,item2;

void *producer(int *a)
{
	while(1)
	{

	sem_wait(&empty);
	sem_wait(&mutex1);
	item1++;
	printf("Producer %d produces item : %d \n",a,item1);
	buffer[in]=item1;
	in=(in+1)%6;
	printf("Buffer:%d \n",buffer[in]);
	sem_post(&mutex1);
	sem_post(&full);
	sleep(2);
	}
}

void *consumer(int *a)
{
	while(1)
	{
		sem_wait(&full);
		sem_wait(&mutex1);
		item2=buffer[out];
		printf("Consumer %d consumes item: %d \n",a,item2);
		out=(out+1)%6;
		sem_post(&mutex1);
		sem_post(&empty);
		sleep(1);
	}
}

void main()
{
	int p,c;
	printf("Enter the no of poducers:");
	scanf("%d",&p);
	printf("Enter the no of consumer:");
	scanf("%d",&c);
	sem_init(&empty,0,6);
	sem_init(&full,0,0);
	sem_init(&mutex1,0,1);
	pthread_t th1[10],th2[10];

	for(int i=0;i<p;i++)
	{
		pthread_create(&th1[i],NULL,&producer,(int *)i);
	}
	for(int j=0;j<c;j++)
	{
		pthread_create(&th2[j],NULL,&consumer,(int *)j);
	}
	for(int i=0;i<p;i++)
	{
		pthread_join(th1[i],NULL);
	}
	for(int j=0;j<c;j++)
	{
		pthread_join(th2[j],NULL);
	}
	

}