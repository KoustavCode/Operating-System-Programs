#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>


int main()
{
	int fd[2];
	int i,c=0,n=0,sp=0;
	char str[100],buf[100];
	pipe(fd);
	pid_t pid;
	pid=fork();

	if(pid==0)
	{
		read(fd[0],buf,sizeof(buf));
		printf("Child");
		printf("The string is:%s",buf);
		exit(0);
	}
	else
	{
		printf("Enter the string : ");
		scanf("%s",str);
		write(fd[1],str,sizeof(str));

	}
	return 0;
}