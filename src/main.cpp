#include "./headers/common.h"
#include "./headers/functions.h"
#include "./headers/localsearch.h"
#include "./headers/utils.h"
#include "./headers/geneticAlgorithm.h"

using namespace std;

int main(int argc,char *argv[])
{
	int N;
	int * matrix;

	matrix = readFile("../instances/fri26.tsp", &N);

	int * tour = (int *) malloc((N+1)*sizeof(int));
	if(argc > 1) srand(stoi(argv[1]));
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

	for(int i = 0; i<N;i++) {
		tour[i] = i;
	}

	tour[N] = 0;
*/
	genRandomTour(N, tour);
	for(int i = 0; i<=N; i++) {
		cout<<tour[i]<<" ";
	}
	cout<<endl;

	int cost = getTourCost(N, tour, matrix);	
	cout<<cost<<endl;

	cost = exchange2(tour,matrix, N, cost);
	for(int i = 0; i<=N; i++) {
		cout<<tour[i]<<" ";
	}
	cout<<endl;
	cost = getTourCost(N, tour, matrix);	
	cout<<cost<<endl;

	geneticAlg(N, tour, matrix, 4, 4);

	free(matrix);
	free(tour);
	return 0;
}
