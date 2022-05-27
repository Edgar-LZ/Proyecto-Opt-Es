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
	int i = 0, j = 0;

	while(i==j) {
		i = rand() % psize;
		j = rand() % psize;
	}
	int ci = getTourCost(N, p+i*(N+1), costs);
	int cj = getTourCost(N, p+j*(N+1), costs);
	return ci<cj ? i:j; // Best solution from the two

}

void oxMerge(vector<int> &arr, int refarr[], int p, int q, int r)
{
	const int n1 =  q-p+1;
	const int n2 = r-q;	
	int L[n1] , R[n2];
	
	for(int i = 0; i< n1; i++) L[i] = arr[p+i];
	for(int j = 0; j<n2; j++) R[j] = arr[q+1+j];
	
	int i = 0;
	int j = 0;
	int k = p;

	while(k < r+1 && i<n1 && j<n2) {
		if( refarr[L[i]] <= refarr[R[j]] ) {
			arr[k] =  L[i];
			k++; i++;
		}
		else {
			arr[k] =  R[j];
			k++; j++;
		}
	
	}
	while( k<r+1 && i<n1) {
		arr[k] = L[i];
		k++;i++;
	}
	while(k<r+1 && j<n2) {
		arr[k] = R[j];
		k++; j++;
	}
}

void oxSort(vector<int> &arr,int refarr[], int p, int r)
{
	if(p<r) {
		int q = (p+r) / 2;
		oxSort(arr, refarr, p, q);
		oxSort(arr, refarr, q+1, r);
		oxMerge(arr, refarr, p, q, r);
	}

}

/* Ordered Crossover Operator for the Genetic Algorithm
 * input: N -> size of the solution
 *		  int * p1, p2 -> pointers to parent solutions
 *		  int * c1, c2 -> pointers to child solutions
 *
 *
 * */
void orderedX(int N, int * p1, int * p2, vector <int> &c1, vector<int> &c2 )
{
	vector<int> selected, reorder1, reorder2;
	int order1[N], order2[N];

	memset(order1, 0, sizeof(order1));
	memset(order2, 0, sizeof(order2));

	for(int i = 0; i<= N ; i++) {
		c1[i]=  *(p1+i);
		c2[i] = *(p2+i);
	}

	int frac =  N * 0.3 ; // Needs fixing, random selection or tuning
	int counter = 0;
	for (int i = 1; i< N; i++) {
		if( rand() % N < frac) {
			selected.push_back(i);
			reorder1.push_back(*(p1+i));
			reorder2.push_back( *(p2+i));
			counter++;
		}
		order1[*(p1 + i)] = i;
		order2[*(p2 + i)] = i;
	}
	oxSort(reorder1, order2, 0, counter-1);
	oxSort(reorder2, order1, 0, counter-2);
	for(int i = 0; i<counter; i++) {
		c1[selected[i]] = reorder1[i];
		c2[selected[i]] = reorder2[i];
	}
	cout << "----PARENTS----"<<endl;
	for(int i = 0; i<=N; i++) {
		cout << *(p1+i)<< " ";
	}cout<<endl;
	for(int i =0; i<=N; i++) {
		cout<<*(p2+i)<<" ";
	}cout<<endl;
	cout << "----CHILDREN----"<<endl;
	for(int i = 0; i<=N; i++) {
		cout << c1[i]<< " ";
	}cout<<endl;
	for(int i =0; i<=N; i++) {
		cout<<c2[i]<<" ";
	}cout<<endl;

}

void swapMutation(int N, vector<int> &csol, float p)
{
	int sel, tmp;
	for(int i = 1; i<N; i++) {
		if(rand() %N < p*N) {
			while ( (sel = rand() % (N-1) + 1 ) == i );
			tmp = csol[i];
			csol[i] =  csol[sel];
			csol[sel] =  tmp;
		}
	}
	if(rand() %N < p*N) {
		sel = rand() % (N-1) + 1;
		tmp =  csol[0];
		csol[0] = csol[sel];
		csol[sel] = tmp;
		csol[N] = csol[0];
	}
	cout << "----MUTATION----"<<endl;
	for(int i = 0; i<=N; i++) {
		cout << csol[i]<< " ";
	}cout<<endl;
	for(int i =0; i<=N; i++) {
		cout<<csol[i]<<" ";
	}cout<<endl;

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
	//int ch[(N+1)*psize]; // Array to store the descendance
	vector<vector<int>> ch(psize, vector<int>(N+1,0));
	
	for(int i = 0; i< psize; i++) { // Generate initial population at random
		genRandomTour(N, p+i*(N+1));
	}
	//printPopulation(N, p, psize);
	for(int i =0; i<gens; i++) {
		int j=0;
	//	for(int j = 0; j<psize; j+=2) {
			int p1 = randomTournament(N, p, psize, costs);
			int p2 = randomTournament(N, p, psize, costs);
			orderedX(N, p+p1*(N+1), p+p2*(N+1), ch[j], ch[j+1]); // Ordered Crossover
			swapMutation(N, ch[j], 1.0 / N);
			swapMutation(N, ch[j+1], 1.0 / N);
			
			// TODO: implement mutation
			// TODO: Sort children from best to worst
			// TODO: Change worst child for the best solution in the population
	//	}
	}

	return 0;

}

