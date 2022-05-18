#include "./headers/common.h"
#include "./headers/functions.h"
#include "./headers/localsearch.h"

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

	matrix = readFile("../instances/fri26.tsp", &N);

	int * tour = (int *) malloc((N+1)*sizeof(int));
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
		cout<<tour[i]<<" ";
	}
	cout<<endl;

	int cost = getTourCost(N, tour, matrix);	
	cout<<cost<<endl;

	cout << exchange2(tour,matrix, N, cost)<<endl;
	for(int i = 0; i<=N; i++) {
		cout<<tour[i]<<" ";
	}
	cout<<endl;
	cost = getTourCost(N, tour, matrix);	
	cout<<cost<<endl;





	free(matrix);
	free(tour);
	return 0;
}
