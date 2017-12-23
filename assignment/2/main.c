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
#include "pwd.h"
#include "echo.h"
#include "parse.h"
#include "cd.h"
#include "global.h"
int par,pro;
typedef struct bgp{
	char prnam[200];
	pid_t pid;
	struct bgp *next;
}bgp;
/*void childhandler()
  {
  if(par==0)
  {
  int status;
  waitpid(-1,&status,0);
  fprintf(stderr,"\n%s with PID %d Has Exited Normally\n",argv[0],pro);
  }
  return;
  }*/
bgp *bp;
int j,pf;
void insertbgp(char name[200],pid_t pid)
{
	bgp *temp1=(bgp *)malloc(sizeof(bgp));
	strcpy(temp1->prnam,name);
	temp1->pid=pid;
	temp1->next=NULL;
	if(bp==NULL)
		bp=temp1;
	else
	{
		bgp *temp=bp;
		while(temp->next!=NULL)
			temp=temp->next;
		temp->next=temp1;
	}
}
void execute(char **argv);
void delbgp(pid_t pid)
{
	if(bp!=NULL)
	{
		bgp *temp=bp;
		if(bp->pid==pid)
		{
			bp=bp->next;
			free(temp);
		}
		else
		{
			bgp *temp2;
			while(temp!=NULL&&temp->pid!=pid)
			{
				temp2=temp;
				temp=temp->next;
			}
			if(temp!=NULL)
			{
				temp2->next=temp->next;
				free(temp);
			}
			else
				;
		}
	}
}
void cmp()
{
	char hostname[1024];
	char *username;
	username=getenv("LOGNAME");
	prpath=getcwd(NULL,0);
	gethostname(hostname , sizeof(hostname));
	if(strstr(prpath,stpath))
	{
		strcpy(pwd,prpath+strlen(stpath));
		printf("<%s@%s:~%s>",username, hostname,pwd);
	}
	else
	{
		printf("<%s@%s:%s>",username, hostname,prpath);
	}
}
void  execute(char **argv)
{
	pid_t  pid;
	int status;
	if ((pid = fork()) < 0) {     
		fprintf(stderr,"forking child process failed\n");
		exit(1);
	}
	else if (pid == 0) { 	
		//par=0;    
		if (execvp(*argv, argv) < 0) {     
			fprintf(stderr,"Error executing the comand:No such file or directory\n");
			//kill(getpid(),SIGTERM);
			exit(1);
		}
	}
	else { 
		pro=pid;
		if(flag==0)
		{
			while (wait(&status) != pid);      
		} 
		else
		{
			insertbgp(argv[0],pid);
			return ;

		}
		return;
	}
}
int main()
{
	stpath=getcwd(NULL,0);
	int flg=0,status;
	char *input;
	size_t len=0;
	//char *prpath;
	while(1==1)
	{
		flag=0;
		//signal(SIGCHLD,handle);
		//	perror("signal not caught\n");
		cmp();
		char str[1000];
		getline(&input,&len,stdin);
		input[strlen(input)-1]='\0';
		strcpy(str,input);
		//gets(input);
		char *token;
		token=strtok(input,";");
		bgp *te = bp;


		while(te!=NULL)
		{
			bgp* next=te->next;
			if(waitpid(te->pid,&status,WNOHANG)==-1)
			{
				fprintf(stderr,"Process with pid %d exited normally\n",te->pid);
				delbgp(te->pid);
			}
			te=next;
		}
		while(token!=NULL)
		{
			pf=0;
			int len=strlen(token),a;
			parse(token,argv);

			int i=0;
			while(argv[i]!=NULL)
				i++;

			//	printf("%c",argv[0][strlen(argv[0])-1]);
			if(strcmp(argv[i-1],"&")==0)
			{
				flag=1;
				argv[i-1]='\0';
			}
			if(strcmp(argv[0],"pwd")==0)
				pwdi();
			else if(strcmp(argv[0],"cd")==0)
			{
				//printf("%s",argv[1]);
				if (argv[1]==NULL|| (strcmp(argv[1],"~")==0) || strcmp(argv[1],"~/")==0)
					chdir(stpath);
				else
					cd(argv[1]);
			}
			else if(strcmp(argv[0],"echo")==0)
			{
				if(strcmp(argv[1],"~")==0)
				{
					char st[100];
					strcpy(st,stpath);
					puts(st);
				}
				else if(argv[1][0]=='"')
				{
					echoi(str);
				}
				else
					echo();
			}
			else if(argv[0][strlen(argv[0])-1]=='&')
			{
				argv[0][strlen(argv[0])-1]='\0';
				flag=1;
				execute(argv);
			}
			else if(strcmp("exit",argv[0])==0)
				exit(0);
			else if(strcmp("pinfo",argv[0])==0)
			{
				FILE *fp;
				flg=0;
				char buf1[1256],buf2[1256];
				int pid;
				char var[1256],state;
				long unsigned int size;
				if(argv[1]==NULL)
				{
					sprintf(buf1,"/proc/%d/stat",getpid());                                
					sprintf(buf2,"/proc/%d/exe",getpid());
				}
				else
				{
					sprintf(buf1,"/proc/%s/stat",(argv[1]));
					sprintf(buf2,"/proc/%s/exe",(argv[1]));
				}
				if((fp=fopen(buf1,"r"))!=NULL)
				{
					fscanf(fp,"%d %*s %c %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %lu %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d",&pid,&state,&size);  
					fclose(fp);
					printf("pid -- %d\nProcess Status -- %c\nmemory -- %lu\n",pid,state,size);
					readlink(buf2,var,1256);
					if(strstr(var,stpath))
					{
						char fi[1000]="~";
						strcat(fi,var+strlen(stpath));
						printf("Executable Path -- %s\n",fi);                           
					}
					else
						printf("Executable Path -- %s\n",var);
				}
				else
					fprintf(stderr,"No such process\n");
			}
			else
				execute(argv);
			token=strtok(NULL,";");
		}
	}
}
