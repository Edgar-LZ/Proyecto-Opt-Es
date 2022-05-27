#include "./headers/utils.h"

int getTourCost(int N, int tour[], int matrix[])
{
	int cost = 0;
	for(int i = 0; i<N;i++){
		cost+= matrix[tour[i]*N + tour[i+1]];
	}

	return cost;
}

void genRandomTour(int N, int * tour)
{
	int i;
	int nodes[N+1];
	for(i = 0; i<N; i++) {
		nodes[i] =i;
	}
	
	int p = N;
	for(i = 0; i<N; i++) {
		int sel = rand() % p;
		tour[i] = nodes[sel];
		int tmp = nodes[sel];
		nodes[sel] =  nodes[p-1];
		nodes[p-1] = tmp;
		p--;
	}
	tour[N] = tour[0];

}
