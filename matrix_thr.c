#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int **a, **b, **s, r2, c2, r1, c1, i, j;

void *inputMatrices()
{
	pthread_mutex_lock(&mutex1);
	printf("\nEnter the number of rows and columns : ");
	scanf("%d %d", &r1, &c1);

	a = (int **)malloc(c1 * sizeof(int*));
	b = (int**)malloc(c1 * sizeof(int*));
	s = (int**)malloc(c1 * sizeof(int*));
	for(i = 0; i < r1; i++)
	{
		a[i] = (int*)malloc(r1 * sizeof(int));
		b[i] = (int*)malloc(r1 * sizeof(int));
		s[i] = (int*)malloc(r1 * sizeof(int));
	}

	printf("Enter the first matrix :\n");
	for(i = 0; i < r1; i++)
		for(j = 0; j < c1; j++)
			scanf("%d", &a[i][j]);

	printf("\nEnter the number of rows and columns : ");
	scanf("%d %d", &r2, &c2);
	printf("Enter the second matrix :\n");
	for(i = 0; i < r2; i++)
		for(j = 0; j < c2; j++)
			scanf("%d", &b[i][j]);

	pthread_mutex_unlock(&mutex1);
}

void printSum()
{
	for (int i = 0; i < r1; ++i)
	{
		for (int j = 0; j < c1; ++j)
		{
			printf("%d ", s[i][j]);
		}
		printf("\n");
	}
}

void *addMatrices()
{
	pthread_mutex_lock(&mutex1);
	for (int i = 0; i < r1; ++i)
	{
		for (int j = 0; j < c1; ++j)
		{
			s[i][j] = a[i][j] + b[i][j];
		}
	}
	pthread_mutex_unlock(&mutex1);

	printSum();
}

int main()
{
	pthread_t thread1, thread2;

	printf("Bhai 1\n");

	pthread_create(&thread1, NULL, &inputMatrices, NULL);
	pthread_create(&thread2, NULL, &addMatrices, NULL);

	printf("Bhai 2\n");

	pthread_join(thread1, NULL);
	printf("Bhai 3\n");
	pthread_join(thread2, NULL);
	printf("Bhai 4\n");


	return 0;
}


/*
pthread_create() takes 4 arguments.
The first argument is a pointer to thread_id 
which is set by this function.

The second argument specifies attributes. 
If the value is NULL, then default attributes shall be used.

The third argument is name of function to be executed
for the thread to be created.

The fourth argument is used to pass arguments to thread.

The pthread_join() function for threads is the equivalent of wait() 
for processes. 
A call to pthread_join blocks the calling thread until
the thread with identifier equal to the first argument terminates.
*/