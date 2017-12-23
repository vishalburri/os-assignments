#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<dirent.h>
#include<string.h>
int main(int argc,char *argv[])
{
	int i;
	//messages
	const char dmsg1[]="Checking whether the directory has been created:YES \n";
	const char dmsg2[]="Checking whether the directory has been created:NO \n";
	const char dmsg3[]="Checking whether the file has been created:YES \n";
	const char dmsg4[]="Checking whether the file has been created:NO \n";
	const char dmsg5[]="Checking whether the file contents has been reversed:YES \n";
	const char dmsg6[]="Checking whether the file contents has been reversed:NO \n";
	const char dmsg7[]="Checking whether the user  has read access to file:YES \n";
	const char dmsg8[]="Checking whether the user  has read access to file:NO \n";
	const char dmsg9[]="Checking whether the user  has write access to file:YES \n";
	const char dmsg10[]="Checking whether the user  has write access to file:NO \n";
	const char dmsg11[]="Checking whether the user  has execute access to file:YES \n";
	const char dmsg12[]="Checking whether the user  has execute access to file:NO \n";
	const char dmsg13[]="Checking whether the group  has read access to file:YES \n";
	const char dmsg14[]="Checking whether the group  has read access to file:NO \n";
	const char dmsg15[]="Checking whether the group  has write access to file:YES \n";
	const char dmsg16[]="Checking whether the group  has write access to file:NO \n";
	const char dmsg17[]="Checking whether the group  has execute access to file:YES \n";
	const char dmsg18[]="Checking whether the group  has execute access to file:NO \n";
	const char dmsg19[]="Checking whether the others  has read access to file:YES \n";
	const char dmsg20[]="Checking whether the others  has read access to file:NO \n";
	const char dmsg21[]="Checking whether the others  has write access to file:YES \n";
	const char dmsg22[]="Checking whether the others  has write access to file:NO \n";
	const char dmsg23[]="Checking whether the others  has execute access to file:YES \n";
	const char dmsg24[]="Checking whether the others  has execute access to file:NO \n";
	const char dmsg25[]="Checking whether the user  has read access to directory:YES \n";
	const char dmsg26[]="Checking whether the user  has read access to directory:NO \n";
	const char dmsg27[]="Checking whether the user  has write access to directory:YES \n";
	const char dmsg28[]="Checking whether the user  has write access to directory:NO \n";
	const char dmsg29[]="Checking whether the user  has execute access to directory:YES \n";
	const char dmsg30[]="Checking whether the user  has execute access to directory:NO \n";
	const char dmsg31[]="Checking whether the group  has read access to directory:YES \n";
	const char dmsg32[]="Checking whether the group  has read access to directory:NO \n";
	const char dmsg33[]="Checking whether the group  has write access to directory:YES \n";
	const char dmsg34[]="Checking whether the group  has write access to directory:NO \n";
	const char dmsg35[]="Checking whether the group  has execute access to directory:YES \n";
	const char dmsg36[]="Checking whether the group  has execute access to directory:NO \n";
	const char dmsg37[]="Checking whether the others  has read access to directory:YES \n";
	const char dmsg38[]="Checking whether the others  has read access to directory:NO \n";
	const char dmsg39[]="Checking whether the others  has write access to directory:YES \n";
	const char dmsg40[]="Checking whether the others  has write access to directory:NO \n";
	const char dmsg41[]="Checking whether the others  has execute access to directory:YES \n";
	const char dmsg42[]="Checking whether the others  has execute access to directory:NO \n";
	char st[100];
	//create filestat
	
	strcat(st,"output_");
	strcat(st,argv[1]);
	struct stat fileStat;
	
	stat("Assignment",&fileStat);
	if(fileStat.st_mode & (S_IRUSR))
	write(STDOUT_FILENO,dmsg25,sizeof(dmsg25)-1);
	else
	write(STDOUT_FILENO,dmsg26,sizeof(dmsg26)-1);
	
	if(fileStat.st_mode & (S_IWUSR))
	write(STDOUT_FILENO,dmsg27,sizeof(dmsg27)-1);
	else
	write(STDOUT_FILENO,dmsg28,sizeof(dmsg28)-1);
	if(fileStat.st_mode & (S_IXUSR))
	write(STDOUT_FILENO,dmsg29,sizeof(dmsg29)-1);
	else
	write(STDOUT_FILENO,dmsg30,sizeof(dmsg30)-1);
	if(fileStat.st_mode & (S_IRGRP))
	write(STDOUT_FILENO,dmsg31,sizeof(dmsg31)-1);
	else
	write(STDOUT_FILENO,dmsg32,sizeof(dmsg32)-1);
	
	if(fileStat.st_mode & (S_IWGRP))
	write(STDOUT_FILENO,dmsg33,sizeof(dmsg33)-1);
	else
	write(STDOUT_FILENO,dmsg34,sizeof(dmsg34)-1);
	if(fileStat.st_mode & (S_IXGRP))
	write(STDOUT_FILENO,dmsg35,sizeof(dmsg35)-1);
	else
	write(STDOUT_FILENO,dmsg36,sizeof(dmsg36)-1);
	if(fileStat.st_mode & (S_IROTH))
	write(STDOUT_FILENO,dmsg37,sizeof(dmsg37)-1);
	else
	write(STDOUT_FILENO,dmsg38,sizeof(dmsg38)-1);
	
	if(fileStat.st_mode & (S_IWOTH))
	write(STDOUT_FILENO,dmsg39,sizeof(dmsg39)-1);
	else
	write(STDOUT_FILENO,dmsg40,sizeof(dmsg40)-1);
	if(fileStat.st_mode & (S_IXOTH))
	write(STDOUT_FILENO,dmsg41,sizeof(dmsg41)-1);
	else
	write(STDOUT_FILENO,dmsg42,sizeof(dmsg42)-1);
	//checking dir is created or not
	int f1=open(argv[1],0400);
	DIR* dir=opendir("Assignment");
	if(dir)
	{
		write(STDOUT_FILENO,dmsg1,sizeof(dmsg1)-1);
		closedir(dir);
	}
	if(!dir)
	{
		write(STDOUT_FILENO,dmsg2,sizeof(dmsg2)-1);
	}
	chdir("Assignment");
	


	stat(st,&fileStat);
	//if else statements checking permissions
	if(fileStat.st_mode & (S_IRUSR))
	write(STDOUT_FILENO,dmsg7,sizeof(dmsg7)-1);
	else
	write(STDOUT_FILENO,dmsg8,sizeof(dmsg8)-1);
	
	if(fileStat.st_mode & (S_IWUSR))
	write(STDOUT_FILENO,dmsg9,sizeof(dmsg9)-1);
	else
	write(STDOUT_FILENO,dmsg10,sizeof(dmsg10)-1);
	if(fileStat.st_mode & (S_IXUSR))
	write(STDOUT_FILENO,dmsg11,sizeof(dmsg11)-1);
	else
	write(STDOUT_FILENO,dmsg12,sizeof(dmsg12)-1);
	if(fileStat.st_mode & (S_IRGRP))
	write(STDOUT_FILENO,dmsg13,sizeof(dmsg13)-1);
	else
	write(STDOUT_FILENO,dmsg14,sizeof(dmsg14)-1);
	
	if(fileStat.st_mode & (S_IWGRP))
	write(STDOUT_FILENO,dmsg15,sizeof(dmsg15)-1);
	else
	write(STDOUT_FILENO,dmsg16,sizeof(dmsg16)-1);
	if(fileStat.st_mode & (S_IXGRP))
	write(STDOUT_FILENO,dmsg17,sizeof(dmsg17)-1);
	else
	write(STDOUT_FILENO,dmsg18,sizeof(dmsg18)-1);
	if(fileStat.st_mode & (S_IROTH))
	write(STDOUT_FILENO,dmsg19,sizeof(dmsg19)-1);
	else
	write(STDOUT_FILENO,dmsg20,sizeof(dmsg20)-1);
	
	if(fileStat.st_mode & (S_IWOTH))
	write(STDOUT_FILENO,dmsg21,sizeof(dmsg21)-1);
	else
	write(STDOUT_FILENO,dmsg22,sizeof(dmsg22)-1);
	if(fileStat.st_mode & (S_IXOTH))
	write(STDOUT_FILENO,dmsg23,sizeof(dmsg23)-1);
	else
	write(STDOUT_FILENO,dmsg24,sizeof(dmsg24)-1);

	
	//checking file is there or not
	if(access(st,F_OK)!=-1)
	{
		write(STDOUT_FILENO,dmsg3,sizeof(dmsg3)-1);
	}
	if(access(st,F_OK)==-1)
	{
		write(STDOUT_FILENO,dmsg4,sizeof(dmsg4)-1);
	}
	int f2;
	char buff1,buff2;
	f2=open(st,0400);
	//checking each character from front and back
	int size=lseek(f1,(off_t) 0,SEEK_END);
	int p,flag=0,q;
	for(i=0;i<=size-2;i++){
		lseek(f2,(off_t) i,SEEK_SET);
		lseek(f1,(off_t) size-2-i,SEEK_SET);
		p=read(f1,&buff1,1);
		q=read(f2,&buff2,1);
		if(buff1!=buff2)
		{
		
			flag=1;
			break;
		}
	}
	if(flag==0)
		write(STDOUT_FILENO,dmsg5,sizeof(dmsg5)-1);
	if(flag==1)
		write(STDOUT_FILENO,dmsg6,sizeof(dmsg6)-1);
	return 0;
}
