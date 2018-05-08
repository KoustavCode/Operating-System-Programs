#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>
#include<math.h>

int r,c;
int **a;int **b,**co;
sem_t s;
void* get_matrix(void* temp)
{
	printf("Enter the no of rows:");
	scanf("%d",&r);
	printf("Enter the no of column:");
	scanf("%d",&c);
	b=(int **)malloc(c*sizeof(int*));
	a=(int **)malloc(c*sizeof(int*));

	for (int i = 0; i < c; ++i)
	{
		a[i] = (int*)malloc(r*sizeof(int));
		b[i] = (int*)malloc(r*sizeof(int));
	}

	printf("Enter the elements of matrix 1");
	for(int i=0;i<r;i++)
	{
		for(int j=0;j<c;j++)
		{
			scanf("%d",&a[i][j]);
		}
	}
	printf("Enter the elements of matrix 2");
	for(int i=0;i<r;i++)
	{
		for(int j=0;j<c;j++)
		{
			scanf("%d",&b[i][j]);
		}
	}
	sem_post(&s);

}

void* matrix_add(void* temp)
{
	sem_wait(&s);
	co=(int **)malloc(c*sizeof(int*));
	for (int i = 0; i < c; ++i)
		co[i] = (int*)malloc(r*sizeof(int));

	for(int i=0;i<r;i++)
	{
		for(int j=0;j<c;j++)
		{
			co[i][j]=a[i][j]+b[i][j];
		}
	}
	printf("The added matrix is:");

	for(int i=0;i<r;i++)
	{
		for(int j=0;j<c;j++)
		{
			printf("%d",co[i][j]);
		}
		printf("\n");
	}
	sem_post(&s);
}

int main()
{
	pthread_t tid1,tid2;
	pthread_create(&tid1,NULL,&get_matrix,NULL);
	pthread_create(&tid1,NULL,&matrix_add,NULL);
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	return 0;
	

}