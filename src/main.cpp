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
	int cost;
	int * tour;
	string fileIn, fileOut, method, crossover;
	int locs;
	ofstream ofile;


	if(argc > 1) {
		srand(stoi(argv[1])); // Seed for random generation
		fileIn = argv[2];
		matrix = readFile(fileIn, &N);
		tour = (int *) malloc((N+1)*sizeof(int));
		fileOut = argv[3];
		ofile.open(fileOut);
		method =  argv[4];
		if(method == "genetic") {
			crossover = argv[5];
			locs = stoi(argv[6]);
			if(crossover == "ord") {
				ofile<<geneticAlg(N, tour, matrix, 100, 200, 0, locs)<<endl;; // size, tour, costs, gens, population
			}
			else if(crossover =="inv") {
				ofile<< geneticAlg(N, tour, matrix, 100, 200, 1, locs)<<endl; // size, tour, costs, gens, population
			}
		} else if(method == "localsearch") {
			genRandomTour(N, tour);
			cost =getTourCost(N, tour, matrix);
			ofile<< exchange2(tour,matrix, N, cost)<<endl;
		}
	} else {
		printf("Argument error.\n");
		return 1;
	}
	free(matrix);
	free(tour);
	return 0;
}
