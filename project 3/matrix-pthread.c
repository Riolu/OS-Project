#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

int M;
int K;
int N;

#define MAX 50
int A[MAX][MAX];
int B[MAX][MAX];
int C[MAX][MAX];

struct v
{
	int vi;
	int vj;
};

void *runner(void *param) 
{
	struct v *args;
	args = (struct v*)param;
	int i = args -> vi, j = args -> vj;
	int m, res = 0;
	for(m = 0; m < K; ++m)
	{
		res += A[i][m] * B[m][j];
	}
	C[i][j] = res;
	free(param);
	return NULL;
}

int main()
{
	pthread_t thread[MAX][MAX];
	
	int i, j;

	int rc;

	time_t start, end;	

	struct v *data;	

	printf("please input the M K N\n");
	scanf("%d%d%d", &M, &K, &N);
	printf("input the matrix1 (M*K):\n");
	for(i = 0; i < M; ++i)
		for(j = 0; j < K;++j)
		{
			scanf("%d", &A[i][j]);
		}
	printf("\ninput the matrix2 (K*N)\n");
	for(i = 0; i < K; ++i)
		for(j = 0; j < N; ++j)
		{
			scanf("%d", &B[i][j]);
		}

	start = clock();

	for(i = 0; i < M; ++i) //create the worker threads
		for(j = 0; j < N; ++j)
		{
			data = (struct v*) malloc(sizeof(struct v));
			data -> vi = i;
			data -> vj = j;
			
		   	//create the thread passing it data as a parameter
			rc = pthread_create(&thread[i][j], NULL, runner, data);

			if(rc)
			{
				printf("create error!\n");
				return 0;
			}
			
			
		}

	for(i = 0; i < M; ++i) //wait until the working thread comes to an end
		for(j = 0 ; j < N; ++j)
		{
			pthread_join(thread[i][j], NULL);
		}

	end = clock();
	printf("the running time using multithread is : %f\n", (double)(end-start)/CLOCKS_PER_SEC );
	
	//print the result
	printf("\nthe result: \n"); 
	for(i = 0; i < M; ++i)
	{
		for(j = 0; j < N; ++j)
		{
			printf("%d ", C[i][j]);
		}
		printf("\n");
	}
	
	
	return 0;
}
