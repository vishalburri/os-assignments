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
struct booth
{
int evm;
int max;
int voters;
}booth;
booth a[1000];

int main()
{
	int n;
	//int readnum[1000];
	printf("enter no of booths:");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
	printf("enter number of voters:");
	scanf("%d",&a[i].voters);
	printf("enter number of evm's:");
	scanf("%d",&a[i].evm);
	printf("enter number of slots:");
	scanf("%d",&a[i].max);
	}
	pthread_t read[n];
	pthread_t write;


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

