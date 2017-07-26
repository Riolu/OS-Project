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


int main()
{
	int i, j, k;

	time_t start, end;	

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

	int res=0;

	for (i=0; i<M; ++i)
	{
		for (j=0; j<N; ++j)
		{
			for (int k=0; k<K; ++k)
			{
				res += A[i][k] * B[k][j]; 			
			}
			C[i][j] = res;			
		}
	}
	
	end = clock();
	printf("the running time is : %f\n", (double)(end-start)/CLOCKS_PER_SEC );
	

	
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
