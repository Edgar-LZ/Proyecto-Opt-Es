#include "./headers/localsearch.h"

void exchange2Opt( int i, int j, int * tour)
{
	int st = i;
	int en = j;
	while(st<en) {
		int tmp = *(tour+st);
		*(tour+st) = *(tour + en);
		*(tour+en) = tmp;
		st++; en--;
	}
}

void exchange2Opt( int i, int j, vector<int> &tour)
{
	int st = i;
	int en = j;
	while(st<en) {
		int tmp = tour[st];
		tour[st] = tour[en];
		tour[en] = tmp;
		st++; en--;
	}
}


int exchange2( int * tour, int *  costs, int N, int current)
{
	int i, j, delta;
	bool improved = true;
	
	while(improved){
		improved = false;
		for(i=1; i<N-1; i++ ) {
			for(j=i+1; j<N; j++) {
				delta = - costs[N*tour[i-1]+tour[i]] - costs[N*tour[j]+tour[j+1]]
					+ costs[N*tour[i]	+ tour[j+1]] + costs[N*tour[i-1]+tour[j]];
				if(delta < 0) {
					exchange2Opt(i, j, tour);
					current+=delta; // Update cost when there is improvement
					improved = true;
				}
			}
		}

	}
	return current;
}

int exchange2( vector<int>  &tour, int *  costs, int N, int current)
{
	int i, j, delta;
	bool improved = true;
	
	while(improved){
		improved = false;
		for(i=1; i<N-1; i++ ) {
			for(j=i+1; j<N; j++) {
				delta = - costs[N*tour[i-1]+tour[i]] - costs[N*tour[j]+tour[j+1]]
					+ costs[N*tour[i]	+ tour[j+1]] + costs[N*tour[i-1]+tour[j]];
				if(delta < 0) {
					exchange2Opt(i, j, tour);
					current+=delta; // Update cost when there is improvement
					improved = true;
				}
			}
		}

	}
	return current;
}

