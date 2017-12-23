#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
#include<signal.h>
#include "global.h"
void echo()
{
	int i=1;
	while(argv[i]!=NULL)
	{

		printf("%s",argv[i]);
		printf(" ");
		i++;
	}
	printf("\n");
}
void echoi(char str[])
{
int i,fl=0;
	for(i=4;i<strlen(str)-1;i++)
	{
		if(str[i]==34 || fl==0)
			fl=1;
		else
		printf("%c",str[i]);
	}
	printf("\n");
}
