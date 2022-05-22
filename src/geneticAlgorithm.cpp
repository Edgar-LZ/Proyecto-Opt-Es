#include "./headers/geneticAlgorithm.h"
/* 
 * For testing: Prints the population of the Genetic Algorithm
 * input: int N -> size of the solution, 
 *		  int p[] -> populartion
 *		  int psize -> size of the population
*/
void printPopulation(int N, int p[], int psize)
{

	for(int i = 0; i<psize; i++) { 
		for(int j = 0; j<=N; j++) {
			cout<<p[i*(N+1) + j]<<" ";
		}
			cout<<endl;
	}

}
/*
 * Takes two solutions at random from the population and returns the index to 
 * the best of the two.
 * input: int N -> size of the solution
 *		  int p[] -> population
 *		  int psize -> size of the population
 *		  int * costs -> cost matrix
 * output: int -> index of the best of two solutions selected at random
 * */
int randomTournament(int N, int p[], int psize, int * costs) {
	int i = 0; j = 0;

	while(i==j) {
		i = rand() % psize;
		j = rand() % psize;
	}
	int ci = getTourCost(N, p+i*(N+1), costs);
	int cj = getTourCost(N, p+j*(N+1), costs);
	return ci<cj ? ci:cj; // Best solution from the two

}
/*
 * Genetic Algorithm for the TSP
 *
 * input: int N -> size of a solution
 *		  int * tour -> pointer to the solution array
 *		  int * costs -> pointer to the array representing the cost matrix
 *		  int gens -> number of generations
 *		  int psize -> size of the population
 *	output: int -> cost of the best solution
 *			stores the best solurion in tour
 * */
int geneticAlg(int N, int * tour, int * costs, int gens, int psize)
{
	int p[(N+1)*psize]; // Array to store the population
	int ch[(N+1)*psize]; // Array to store the descendance
	
	for(int i = 0; i< psize; i++) { // Generate initial population at random
		genRandomTour(N, p+i*(N+1));
	}
	//printPopulation(N, p, psize);
	for(int i =0; i<gens; i++) {
		int p1 = randomTournament(N, p, psize, costs);
		int p2 = randomTournament(N, p, psize, costs);
		// TODO: implement recombination
		// TODO: implement mutation
		// TODO: Sort children from best to worst
		// TODO: Change worst child for the best solution in the population
	
	}

	return 0;

}

