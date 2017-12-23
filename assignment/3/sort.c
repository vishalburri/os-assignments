#include<stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
#include<signal.h>
#include<limits.h>
#include <sys/shm.h>
#include <sys/types.h>
pid_t ipid;

void selsort(int array[],int l,int r);
void msort(int a[],int l,int r);
void merge(int arr[], int l, int m, int r);
int main()
{
	int n,i;
	printf("Enter value of n:\n");
	scanf("%d",&n);
	int arr[n];
	for(i=0;i<n;i++)
		scanf("%d",&arr[i]);
	int id,len;
	size_t size;
	int *a;
	key_t key;
	ipid=getpid();
	size=n*sizeof(int);
	key=IPC_PRIVATE;
	if ((id = shmget(key, size, IPC_CREAT | 0666)) == -1) {
		perror("shmget error");
		exit(1);
	}
	a=shmat(id,NULL,0);
	for(i=0;i<n;i++)
		a[i]=arr[i];

	msort(a,0,n-1);
	for(i=0;i<n;i++)
		printf("%d\n",a[i]);
	return 0;
}
void msort(int a[],int l,int r)
{
	int status;
	pid_t pid,pid2;
	int m,len;
	len=r-l+1;
	m=l+len/2-1;
	if (len <= 5)
	{
		selsort(a,l,r);
		return ;
	}
	else
	{
		pid=fork();
		if(pid < 0)
		{
			perror("fork error");
			_exit(-1);
		}
		else if(pid == 0)
		{
			msort(a, l, m);
			_exit(0);
		}
		else
		{
			pid2=fork();
			if(pid2<0)
			{
				perror("fork error");
				_exit(-1);
			}
			else if(pid2==0)
			{
				msort(a, m+1, r);
				_exit(0);
			}

		}
		waitpid(pid,&status,0);
		waitpid(pid2,&status,0);
		merge(a,l,m,r);
	}
}
void selsort(int array[],int l,int r)
{

	int c,d;
	int position,swap;
	for ( c = l ; c <= ( r - 1 ) ; c++ )
	{
		position = c;

		for ( d = c + 1 ; d <=r ; d++ )
		{
			if ( array[position] > array[d] )
				position = d;
		}
		if ( position != c )
		{
			swap = array[c];
			array[c] = array[position];
			array[position] = swap;
		}
	}
}
void merge(int arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 =  r - m;
	int L[n1], R[n2];
	for(i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for(j = 0; j < n2; j++)
		R[j] = arr[m + 1+ j];
	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}
	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}
	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}
