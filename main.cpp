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
#include "sorting_algs.h"


#define DEBUG 1





typedef void (*sort_func)(int[], int n);

void mergesort_wrapper(int a[], int n)
{
	mergesort(a, 0, n-1);
}

void qsort_wrapper(int a[], int n)
{
	quicksort(a, 0, n-1);
}

void iter_qsort_wrapper(int a[], int n)
{
	iter_quicksort(a, 0, n-1);
}

void qsort_insertion_wrapper(int a[], int n)
{
	quick_insertionsort(a, 0, n-1);
}


typedef struct
{
	sort_func func;
	char name[40];
} test_struct;




test_struct tests[] =
{
	{ iterative_merge,          "itermerge" },
	{ heapsort,                 "hsort"     },     
	{ ternary_heapsort,         "trihsort"  },
	{ qsort_wrapper,            "qsort"     },
	{ mergesort_wrapper,        "recmerge"  },
	{ iter_qsort_wrapper,       "iterqsort" },
	{ qsort_insertion_wrapper,  "qinssort"  }
};


#define NUM_ALGS (sizeof(tests)/sizeof(test_struct))
#define NUM_N 12



using namespace std;



int main()
{
	int n_sizes[] = {50, 500, 1000, 5000, 10000, 50000, 100000+3, 500000-5, 1000000, 5000000, 10000000, 50000000};
	int num_n = NUM_N;
	
	
	double table_results[NUM_ALGS][NUM_N];
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

		//loop through selected algorithms it test_struct
		for (int j=0; j<NUM_ALGS; j++) {
			before = clock();
			tests[j].func(temp_array, n_sizes[i]);
			table_results[j][i] = ((double)(clock() - before))/CLOCKS_PER_SEC;

			//check results
#ifdef DEBUG
			for(int j=1; j<n_sizes[i]; j++) {
				if(temp_array[j-1]>temp_array[j]) {
					cout << "\n\n" << "Fail" <<"\n\n";
				}
			}
#endif
			memcpy(temp_array, test_array, n_sizes[i]*sizeof(int)); //reset array
		}


		delete[] temp_array;
		delete[] test_array;
	}

	cout<<setw(50)<<"Sort time in milliseconds"<<endl;
	cout<<setw(10)<<"N";
	int len;
	for (int j=0; j<NUM_ALGS; j++) {
		len = strlen(tests[j].name);
		cout << setw((len > 10) ? len+2 : 10) << tests[j].name;
	}
	cout << endl;
	
	for (int i=0; i<num_n; i++) {
		cout << setw(10) << n_sizes[i];
		for (int j=0; j<NUM_ALGS; j++) {
			len = strlen(tests[j].name);
			cout << setw((len > 10) ? len+2 : 10) << table_results[j][i]*1000;
		}
		cout << endl;
	}


	return 0;
}







