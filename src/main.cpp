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

	matrix = readFile("../instances/pcb442.tsp", &N);

	int * tour = (int *) malloc((N+1)*sizeof(int));
	if(argc > 1) srand(stoi(argv[1])); // Seed for random generation

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
	genRandomTour(N, tour);
	for(int i = 0; i<=N; i++) {
		cout<<tour[i]<<" ";
	}
	cout<<endl;

	cost = getTourCost(N, tour, matrix);	
	cout<<cost<<endl;


	geneticAlg(N, tour, matrix, 100, 200); // size, tour, costs, gens, population
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
