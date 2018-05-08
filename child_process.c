#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
// sleep, wait 
int main()
{
	pid_t pid, pid1;
	int a=10;
	pid=fork();
	pid1 = fork();

	if(pid==0 || pid1 == 0)
	{
		wait(NULL);
		a=a+10;
		printf("In Child process, pid is:%d \n",getpid());
		printf("In child process, parent pid is :%d \n",getppid());
		printf("In child process, the value of a is:%d \n\n", a);

	}
	if(pid>0 || pid1 >0)
	{
		sleep(1);
		printf("In parent process, pid is:%d: \n",getpid());
		printf("In parent process, parent's parent pid is :%d \n",getppid());
		printf("In parent process, the value of a is:%d \n\n", a);

	}
	return 0;
}