#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
	pid_t pid;
	pid=fork();
	pid=fork();

	if(pid<0)
	{
		printf("Error");
		exit(0);

	}
	else if(pid==0)
	{
		printf("In child process: Child Pid:%d  Parent pid=%d \n",getpid(),getpid());
	}
	else
	{
		printf("In the parent process: Parent pid: %d  Child pid:%d \n ",getpid(),getpid());

	}
	return 0;
}