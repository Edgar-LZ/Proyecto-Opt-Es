#include "./headers/geneticAlgorithm.h"
#include "./headers/localsearch.h"
#include "./headers/utils.h"
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
	} /*
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
	}cout<<endl;*/

}
/*
 *	Classical crossover operator using the inversion sequence of a permutation.
 *	Generates valid paths. For each child, each parent provides displacement
 *	information of some of the elements.
 *	input: N -> size of the solution
 *		   int *p1, *p2 -> pointers to the parent solutions
 *		   vector<int> &c1, &c2 -> references to child solutions
 *
 *	Inversion sequence of 6, 2, 3, 1, 7, 5 is 4, 1, 1, 1, 2, 0, 0
 *	It tells us for aj the numbers that precede j in the permutation, but are
 *	greater than j.
 *
 * */
void invX(int N, int * p1, int * p2, vector<int> &c1, vector<int> &c2)
{
	vector<int> invP1, invP2, invC1, invC2;
	int m;
	int point1, point2, tmp;
	for(int i = 0; i<N; i++) {
		invP1.push_back(0);
		invP2.push_back(0);
		invC1.push_back(0);
		invC2.push_back(0);
		m = 0;
		while( *(p1+m) != i ) { // Generate inversion sequence for p1
			if(*(p1+m) > i) {
				invP1[i]++;
			}
			m++;
		}
		m=0;

		while( *(p2+m) != i ) { // Generate inversion sequence for p2
			if(*(p2+m) > i) {
				invP2[i]++;
			}
			m++;
		}

	}/*
	cout << "----PARENTS----"<<endl;
	for(int i = 0; i<=N; i++) {
		cout << *(p1+i)<< " ";
	}cout<<endl;
	for(int i =0; i<=N; i++) {
		cout<<*(p2+i)<<" ";
	}cout<<endl;
	cout << "----INVERSE----"<<endl;
	for(int i = 0; i<N; i++) {
		cout << invP1[i]<< " ";
	}cout<<endl;
	for(int i =0; i<N; i++) {
		cout<< invP2[i]<<" ";
	}cout<<endl;
*/
	point1 = rand() % N;
	while( (point2 = rand()% N) == point1);
	tmp = max(point1, point2);
	point1 = min(point1, point2);
	point2 =  tmp;
	
	int i=0; // Two point crossover operator
	while( i<point1 ) {
		invC1[i] = invP1[i];
		invC2[i] = invP2[i];
		i++;
	}
	while( i<point2 ) {
		invC1[i] = invP2[i];
		invC2[i] = invP1[i];
		i++;
	}
	while( i<N ) {
		invC1[i] = invP1[i];
		invC2[i] = invP2[i];
		i++;
	}
	vector<int> pos(N,-1);
	/*for(int i = N-2; i>=0; i--) {
		for(int j = i; j<N; j++) {
			if(pos[m]>= invC1[i]+1) pos[m]++;
			pos[i] = invC1[i]+1;
		}
	}*/
	int empt;
	for(int i = 0; i<N; i++) {
		empt = 0; // Empty spaces
		int j = 0;
		while(empt < invC1[i] +1) {
			if(pos[j] == -1) empt++ ; // Place it on the invC1[i]th empty space
			if(empt == invC1[i]+1) {
				pos[j] = i;
			}
			j++;
		}
	}

	for(int i = 0; i<N; i++)
		c1[pos[i]] = i;
	pos.assign(N,-1);
	/*for(int i = N-2; i>=0; i--) {
		for(int j = i; j<N; j++) {
			if(pos[m]>= invC2[i]+1) pos[m]++;
			pos[i] = invC2[i]+1;
		}
	}*/
	for(int i = 0; i<N; i++) {
		empt = 0; // Empty spaces
		int j = 0;
		while(empt <invC2[i] +1) {
			if(pos[j] == -1) empt++ ; // Place it on the invC1[i]th empty space
			if(empt == invC2[i]+1) {
				pos[j] = i;
			}
			j++;
		}
	}


	for(int i = 0; i<N; i++) {
		c2[pos[i]] = i;
	}

	c1[N] = c1[0];
	c2[N] = c2[0];
	/*
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
	*/
}


/*
 *	Mutation operator for the Genetic Algorithm.
 *	Mutates each element of the array with a probability p.
 *	If the mutation occurs, a random node is selected and swapped with
 *	the current node.
 *	input: N -> size of the solution
 *		   vector <int> &csol -> vector containing the solution to mutate.
 *		   float p -> probability of mutation
 * */
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
	} /*
	cout << "----MUTATION----"<<endl;
	for(int i = 0; i<=N; i++) {
		cout << csol[i]<< " ";
	}cout<<endl;
	for(int i =0; i<=N; i++) {
		cout<<csol[i]<<" ";
	}cout<<endl;*/

}
bool cmp( vector <int> a, vector<int > b, int * costs) {
	int N =  a.size() - 1;
	int ac =  getTourCost(N, a, costs);
	int bc = getTourCost(N, b, costs);
	return ac < bc;
}

/*
 *	Merge function for Merge-Sort Algoritm. Sorts child solutions based o their
 *	cost. Best solutions end in the begininig of the vector.
 *	input: vector<vector<int>> &arr -> Reference to vector containinig child solutions
 *		   int p -> start index
 *		   int q -> middle index
 *		   int r -> end index
 *		   int  * costs -> pointer to array representing the cost matrix
 * */
void chMerge(vector<vector<int>> &arr, int p, int q, int r, int * costs)
{
	const int n1 =  q-p+1;
	const int n2 = r-q;	
	vector<vector<int>> L, R;
	
	for(int i = 0; i< n1; i++) L.push_back(arr[p+i]);
	for(int j = 0; j<n2; j++) R.push_back(arr[q+1+j]);
	
	int i = 0;
	int j = 0;
	int k = p;
	while(k < r+1 && i<n1 && j<n2) {
		if( cmp(L[i], R[j], costs) ) {
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
/*
 *	Merge sort algorithm. Sorts child solutions based on their cost. Best solutions
 *	end in the beginning of the vector.
 *	input: vector<vector<int>> &arr -> Reference vector containing child solutions
 *		   int p -> start index
 *		   int r -> end index
 *		   int * costs -> pointer to array representing the cost matrix
 * */
void chSort(vector<vector<int>> &arr, int p, int r, int * costs)
{
	if(p<r) {
		int q = (p+r) / 2;
		chSort(arr, p, q, costs);
		chSort(arr, q+1, r, costs);
		chMerge(arr, p, q, r, costs);
	}

}

void childToP(int N, vector<int> child, int * p)
{
	for(int i = 0; i<=N; i++) *(p+i) = child[i];
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
	vector<vector<int>> ch(2*psize, vector<int>(N+1,0));
	
	for(int i = 0; i< psize; i++) { // Generate initial population at random
		genRandomTour(N, p+i*(N+1));
	}
	//printPopulation(N, p, psize);
	for(int i =0; i<gens; i++) {
		cout<< i<<endl;
		for(int j = 0; j<2*psize; j+=4) {
			int p1 = randomTournament(N, p, psize, costs);
			int p2 = randomTournament(N, p, psize, costs);
			//orderedX(N, p+p1*(N+1), p+p2*(N+1), ch[j], ch[j+1]); // Ordered Crossover
			//orderedX(N, p+p1*(N+1), p+p2*(N+1), ch[j+2], ch[j+3]); // Ordered Crossover
			invX(N, p+p1*(N+1), p+p2*(N+1), ch[j], ch[j+1]);
			invX(N, p+p1*(N+1), p+p2*(N+1), ch[j+2], ch[j+3]);
			swapMutation(N, ch[j], 1.0 / N);
			swapMutation(N, ch[j+1], 1.0 / N);
			swapMutation(N, ch[j+2], 1.0 / N);
			swapMutation(N, ch[j+3], 1.0 / N);
		}
		for(int j = 0; j< 2*psize; j++) {
			int current = getTourCost(N, ch[i], costs);
			exchange2( ch[i], costs, N, current);
		}
		chSort(ch, 0, 2*psize-1, costs);
		int chbest = getTourCost(N, ch[0], costs);
		int pworst = getTourCost(N, p+(psize-1)*(N+1), costs);
		int pbest = getTourCost(N, p, costs);


		if( i > 0 && chbest > pbest) {
			for(int k = 1; k<psize; k++) {
				childToP(N, ch[k], p + k*(N+1) );
			}
		} else {
			for(int k = 0; k<psize; k++) {
				childToP(N, ch[k], p + k*(N+1) );
			}

		}

		//pworst = getTourCost(N, p+(psize-1)*(N+1), costs);
		cout << pbest<< endl;

	}
	for(int i = 0; i<=N; i++){
		*(tour +i) = *(p+i);
	}

	return 0;

}
