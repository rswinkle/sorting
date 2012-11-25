/*
Written by Robert Winkler

An benchmark program comparing different sorting algorithms
and implementations.
*/




#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <iomanip>
#include "myalgorithms.h"




#define NUMALGS 5
#define NUMTESTS 12


using namespace std;



int main()
{
	int n_sizes[] = {50, 500, 1000, 5000, 10000, 50000, 100000+3, 500000-5, 1000000, 5000000, 10000000, 50000000};
	int num_n = NUMTESTS;
	double table_results[NUMALGS][NUMTESTS];
	clock_t before;

	int *test_array, *temp_array;
	
	for(int i=0; i<num_n; i++) {
		srand(time(NULL));
		test_array = new int[n_sizes[i]];
		temp_array = new int[n_sizes[i]];

		for(int j=0; j<n_sizes[i]; j++) {
			temp_array[j] = test_array[j] = rand() % (2*n_sizes[i]);
		}
		
		cout<<"N = "<<n_sizes[i]<<endl;

		/******   searching algorithms go here *******/
		//use clock() to find time for each algorithm
		
		before = clock();
		iterativemerge(temp_array, n_sizes[i]);
		table_results[0][i] = ((double)(clock() - before))/CLOCKS_PER_SEC;

		//check results
		for(int j=1; j<n_sizes[i]; j++) {
			if(temp_array[j-1]>temp_array[j]) {
				cout << "\n\n" << "Fail" <<"\n\n";
			}
		}
		memcpy(temp_array, test_array, n_sizes[i]*sizeof(int)); //reset array


		before = clock();
		heapsort(temp_array, n_sizes[i]);
		table_results[1][i] = ((double)(clock() - before))/CLOCKS_PER_SEC;
		
		for(int j=1; j<n_sizes[i]; j++) {
			if(temp_array[j-1]>temp_array[j]) {
				cout << "\n\n" << "Fail" <<"\n\n";
			}
		}
		memcpy(temp_array, test_array, n_sizes[i]*sizeof(int)); //reset array

		before = clock();
		ternaryHeapsort(temp_array, n_sizes[i]);
		table_results[2][i] = ((double)(clock() - before))/CLOCKS_PER_SEC;
		
		for(int j=1; j<n_sizes[i]; j++) {
			if(temp_array[j-1]>temp_array[j]) {
				cout << "\n\n" << "Fail" <<"\n\n";
			}
		}
		memcpy(temp_array, test_array, n_sizes[i]*sizeof(int)); //reset array


		before = clock();
		quicksort(temp_array, 0, n_sizes[i]-1);
		table_results[3][i] = ((double)(clock() - before))/CLOCKS_PER_SEC;
		
		for(int j=1; j<n_sizes[i]; j++) {
			if(temp_array[j-1]>temp_array[j]) {
				cout << "\n\n" << "Fail" <<"\n\n";
			}
		}
		memcpy(temp_array, test_array, n_sizes[i]*sizeof(int)); //reset array


		before = clock();
		mergesort(temp_array, 0, n_sizes[i]-1);
		table_results[4][i] = ((double)(clock() - before))/CLOCKS_PER_SEC;
		
		for(int j=1; j<n_sizes[i]; j++) {
			if(temp_array[j-1]>temp_array[j]) {
				cout << "\n\n" << "Fail" <<"\n\n";
			}
		}
		
		delete[] temp_array;
		delete[] test_array;
	}

	cout<<setw(50)<<"Sort time in milliseconds"<<endl;
	cout<<setw(10)<<"N"<<setw(12)<<"itermerge"<<setw(10)<<"hsort"<<setw(10)<<"trihsort"<<setw(10)<<"qsort"<<setw(10)
					<<"recmerge"<<endl<<endl;

	for(int i=0; i<num_n ;i++) {
		cout<<setw(10)<<n_sizes[i]<<setw(12)<<table_results[0][i]*1000<<setw(10)<<table_results[1][i]*1000<<setw(10)
							<<table_results[2][i]*1000<<setw(10)<<table_results[3][i]*1000<<setw(10)
							<<table_results[4][i]*1000<<endl;
	}


	return 0;
}







