#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<time.h>
#include <sys/utsname.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
#include<signal.h>
#include<limits.h>
int buffer,n,wpos=0,size;

int buff[1000],threads=0;

sem_t lo[1000];
sem_t wlo[1000];
int rcount[1000],rcountpost[1000];
void initlock(int i)
{
	sem_init(&lo[i],0,1);
	sem_init(&wlo[i],0,1);
}

void *wri ()
{
	int i,fill=0;
	for(i=0;i<buffer;i++)
	{
		while(buff[i%size]!=0 && rcountpost[i%size]!=n);
		//printf("writer %d enters\n",i%size);
		sem_wait(&wlo[i%size]);
		buff[i%size] = rand()%10000+1;
		rcount[i%size]=0;
		rcountpost[i%size]=0;
		
		wpos++;
		printf("\nvalue written is %d at %d location\n", buff[i%size],i%size);
		//printf("writer %d left\n",i%size);
		sem_post(&wlo[i%size]);
	}
}

void *rea(void * arg)
{
	int i,use=0;
	int *point = (int*)arg;
	int temp = *point;
	for(i=0;i<buffer;i++)
	{
		while(wpos<=i);
		sem_wait(&lo[i%size]);
		rcount[i%size]++;
		if(rcount[i%size]==1)
			sem_wait(&wlo[i%size]); 

		printf("\nvalue read is %d from %d location by %d reader\n",buff[i%size],i%size,temp);
		sem_post(&lo[i%size]);
		sem_wait(&lo[i%size]);
		rcountpost[i%size]++;
		if (rcount[i%size] == n)
		{
			sem_post(&wlo[i%size]); 
		}


	//	printf("reader %d left\n",i%size);
		sem_post(&lo[i%size]);
	}
}

int main()
{
	//int n;
	int readnum[1000];
	printf("enter no of readers:");
	scanf("%d",&n);
	printf("enter number of writes:");
	scanf("%d",&buffer);
	
	printf("enter number of buffersize:");
	scanf("%d",&size);
	pthread_t read[n];
	pthread_t write;

	int i;

	for(i=0;i<size;i++)
		initlock(i);

	pthread_create(&write,NULL,wri,NULL);

	for(i=0;i<n;i++)
		{
		readnum[i]=i;
		pthread_create(&read[i],NULL,rea,(void *)&readnum[i]);
		}
	for(i=0;i<n;i++)
		pthread_join(read[i],NULL);

	pthread_join(write,NULL);

	return 0;
}

