#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

int M;
int K;
int N;

#define MAX 500
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
	
	int i, j, k;

	int rc;

	time_t start1, end1, start2, end2;	

	struct v *data;	

	srand((unsigned)time(NULL));


	for (int n=10;n<=200;n+=10){

		printf("size: %d\n", n);
		M = N = K = n;
		//printf("input the matrix1 (M*K):\n");
		for(i = 0; i < M; ++i)
			for(j = 0; j < K;++j)
			{
				A[i][j] = rand();
			}
		//printf("\ninput the matrix2 (K*N)\n");
		for(i = 0; i < K; ++i)
			for(j = 0; j < N; ++j)
			{
				B[i][j] = rand();
			}


		start1 = clock();

		int res;

		for (i=0; i<M; ++i)
		{
			for (j=0; j<N; ++j)
			{
				C[i][j] = 0;
				for (int k=0; k<K; ++k)
				{
					C[i][j] += A[i][k] * B[k][j]; 			
				}		
			}
		}
	
		end1 = clock();
		printf("the running time is : %f\n", (double)(end1-start1)/CLOCKS_PER_SEC );

	
		start2 = clock();

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

		end2 = clock();
		printf("the running time using multithread is : %f\n", (double)(end2-start2)/CLOCKS_PER_SEC );

	}
	

	
	
	return 0;
}
