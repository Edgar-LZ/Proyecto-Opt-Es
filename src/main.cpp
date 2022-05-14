#include "./headers/common.h"
#include "./headers/functions.h"

using namespace std;
int getTourCost(int N, int tour[], int matrix[])
{
	int cost = 0;
	for(int i = 0; i<N;i++){
		cost+= matrix[tour[i]*N + tour[i+1]];
	}

	return cost;
}

int main()
{
	int N;
	int * matrix;
	int tour[N+1];

	matrix = readFile("../instances/pcb442.tsp", &N);
/*
	for(int i = 0; i <N; i++) {
		for(int j = 0; j<N;j++) {
			cout<<matrix[i*N + j]<<" ";
		}
		cout<<endl;

	}
*/	
/*
	matrix[0] = matrix[N+1] = matrix[2*N + 2] = matrix[3*N+3] =9999;
	matrix[0*N+1] = matrix[1*N+0] = 2;
	matrix[0*N+2] = matrix[2*N+0] = 1;
	matrix[0*N+3] = matrix[3*N+0] = 5;
	matrix[1*N+2] = matrix[2*N+1] = 7;
	matrix[1*N+3] = matrix[3*N+1] = 3;
	matrix[2*N+3] = matrix[3*N+2] = 4;
*/
	for(int i = 0; i<N;i++) {
		tour[i] = i;
	}

	tour[N] = 0;

	for(int i = 0; i<=N; i++) {
		cout<<tour[i]<<endl;
	}

	cout<< getTourCost(N, tour, matrix)<<endl;	


	return 0;
}
