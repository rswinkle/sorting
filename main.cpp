/*
Written by Robert Winkler

An benchmark program comparing different sorting algorithms
and implementations.
*/




#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <algorithm>
#include "sorting_algs.h"






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

int cmp_int_lt(const void* a, const void* b)
{
	int a_ = *(int*)a;
	int b_ = *(int*)b;

	if (a_ < b_)
		return -1;
	if (a_ > b_)
		return 1;

	return 0;
}

void qsort_lib_wrapper(int a[], int n)
{
	qsort(a, n, sizeof(int), cmp_int_lt);
}

void cppsort_wrapper(int a[], int n)
{
	std::sort(a, a+n);
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
	{ qsort_lib_wrapper,        "qsortlib"  },
	{ cppsort_wrapper,          "cppsort"   },
	{ mergesort_wrapper,        "recmerge"  },
	{ iter_qsort_wrapper,       "iterqsort" },
	{ qsort_insertion_wrapper,  "qinssort"  }
};


#define NUM_ALGS (sizeof(tests)/sizeof(test_struct))
#define NUM_N 12






int main()
{
	int n_sizes[] = {50, 500, 1000, 5000, 10000, 50000, 100000+3, 500000-5, 1000000, 5000000, 10000000, 50000000};
	int num_n = NUM_N;
	
	
	double table_results[NUM_ALGS][NUM_N];
	clock_t before;

	int *test_array, *temp_array;
	
	for(int i=0; i<num_n; i++) {
		srand(time(NULL));
		test_array = (int*)malloc(n_sizes[i] * sizeof(int));
		temp_array = (int*)malloc(n_sizes[i] * sizeof(int));

		for(int j=0; j<n_sizes[i]; j++) {
			temp_array[j] = test_array[j] = rand() % (4*n_sizes[i]);
		}
		
		printf("N = %d\n", n_sizes[i]);

		//loop through selected algorithms it test_struct
		for (int j=0; j<NUM_ALGS; j++) {
			before = clock();
			tests[j].func(temp_array, n_sizes[i]);
			table_results[j][i] = ((double)(clock() - before))/CLOCKS_PER_SEC;

			//check results
#ifdef DEBUG
			for(int j=1; j<n_sizes[i]; j++) {
				if(temp_array[j-1] > temp_array[j]) {
					puts("\n\nFail\n");
				}
			}
#endif
			/* reset array */
			memcpy(temp_array, test_array, n_sizes[i]*sizeof(int));
		}


		free(temp_array);
		free(test_array);
	}

	printf("%50s\n", "Sort time in milliseconds");
	printf("%10s", "N");
	int len;
	for (int j=0; j<NUM_ALGS; j++) {
		len = strlen(tests[j].name);
		printf("%*s", ((len > 10) ? len+2 : 10), tests[j].name);
	}
	putchar('\n');
	
	for (int i=0; i<num_n; i++) {
		printf("%10d", n_sizes[i]);
		for (int j=0; j<NUM_ALGS; j++) {
			len = strlen(tests[j].name);
			printf("%*.0f", ((len > 10) ? len+2 : 10), table_results[j][i]*1000);
		}
		putchar('\n');
	}


	return 0;
}








