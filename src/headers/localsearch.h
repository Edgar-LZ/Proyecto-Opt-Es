#ifndef LOC_SEAR_H
	#define LOC_SEAR_H

#include "./common.h"
void exchange2Opt(int i, int j, int * tour);
int exchange2(int * tour, int * costs, int N, int current);
void exchange2Opt(int i, int j, vector<int> &tour);
int exchange2(vector<int> &tour, int * costs, int N, int current);


#endif
