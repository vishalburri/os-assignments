#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

int main(int argc,char *argv[])
{
	int filedes;
	char buffer,out[100];
	int i,s,d,p;
	//creating directory
	mkdir("Assignment",0700);
	//opening file
	filedes=open(argv[1],0400);
	//changing directory
	chdir("Assignment");
	//concatinating output_ and filename
	strcat(out,"output_");
	strcat(out,argv[1]);
	//create filename
	d=creat(out,0600);
	//finding filesize
	int size=lseek(filedes,(off_t) 0,SEEK_END);
	for(i=size-2;i>=0;i--){
		lseek(filedes,(off_t) i,SEEK_SET);
	//read each charater from end and write to file
		p=read(filedes,&buffer,1);
		p=write(d,&buffer,1);
	}
	return 0;
}



