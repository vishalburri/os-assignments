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
void cd(char* a)
{
	int p=chdir(a);
	if(p<0)
		fprintf(stderr,"No such file or dirctory exists\n");
}
