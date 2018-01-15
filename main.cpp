// Written by Robert Winkler
// 
// An benchmark program comparing different sorting algorithms
// and implementations.

#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <algorithm>
#include "sorting_algs.h"

typedef void (*sort_func)(int[], size_t n);

void mergesort_wrapper(int a[], size_t n)
{
	mergesort(a, 0, n-1);
}

void qsort_wrapper(int a[], size_t n)
{
	quicksort(a, 0, n-1);
}

void iter_qsort_wrapper(int a[], size_t n)
{
	iter_quicksort(a, 0, n-1);
}

void qsort_insertion_wrapper(int a[], size_t n)
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

void qsort_lib_wrapper(int a[], size_t n)
{
	qsort(a, n, sizeof(int), cmp_int_lt);
}

void qsort_my_wrapper(int a[], size_t n)
{
	generic_qsort(a, n, sizeof(int), cmp_int_lt);
}

void cppsort_wrapper(int a[], size_t n)
{
	std::sort(a, a+n);
}

typedef struct sort_alg
{
	sort_func func;
	char name[40];
} sort_alg;

/*
sort_alg algorithms[] =
{
	{ iterative_merge,          "itermerge" },
	{ heapsort,                 "hsort"     },
	{ ternary_heapsort,         "trihsort"  },
	{ quad_heapsort,            "quadhsort" },
	{ qsort_wrapper,            "qsort"     },
	{ qsort_lib_wrapper,        "qsortlib"  },
	{ cppsort_wrapper,          "cppsort"   },
	{ mergesort_wrapper,        "recmerge"  },
	{ iter_qsort_wrapper,       "iterqsort" },
	{ qsort_insertion_wrapper,  "qinssort"  }
};

sort_alg algorithms[] =
{
	{ qsort_wrapper,            "qsort"         },
	{ qsort_lib_wrapper,        "qsortlib"      },
	{ qsort_my_wrapper,         "genericqsort"  },
	{ iter_qsort_wrapper,       "iterqsort"     },
	{ qsort_insertion_wrapper,  "qinssort"      }
};
*/

sort_alg algorithms[] =
{
	{ heapsort,                 "hsort"     },
	{ ternary_heapsort,         "trihsort"  },
	{ quad_heapsort,            "quadhsort" }
};

size_t n2_sizes[]      = { 10, 50, 500, 1000, 5000, 10000, 50000 };
size_t n_sizes_small[] = { 10000, 50000, 100000+3, 500000-5, 1000000 };
size_t n_sizes_med[]   = { 10000, 50000, 100000+3, 500000-5, 1000000, 5000000, 10000000, 50000000 };
size_t n_sizes_giant[] = { 500000-5, 1000000, 5000000, 10000000, 50000000, 100000000, 500000000 };
size_t n_sizes[]       = { 500000-5, 1000000, 5000000, 10000000, 50000000, 100000000, 500000000 };

#define NUM_ALGS (sizeof(algorithms)/sizeof(sort_alg))
#define NUM_N (sizeof(n_sizes)/sizeof(size_t))

int main()
{
	int start_n = 0;
	int num_n = NUM_N;

	double table_results[NUM_ALGS][NUM_N];
	clock_t before;

	int *test_array, *temp_array;

	printf("%u %d\n", (unsigned)sizeof(int), INT_MAX);

	size_t i, j, k;
	
	for(i=start_n; i<num_n; ++i) {
		srand(time(NULL));
		test_array = (int*)malloc(n_sizes[i] * sizeof(int));
		temp_array = (int*)malloc(n_sizes[i] * sizeof(int));

		for(j=0; j<n_sizes[i]; ++j) {
			temp_array[j] = test_array[j] = rand();
		}
		
		printf("N = %lu\n", n_sizes[i]);

		//loop through selected algorithms it test_struct
		for (j=0; j<NUM_ALGS; ++j) {
			before = clock();
			algorithms[j].func(temp_array, n_sizes[i]);
			table_results[j][i] = ((double)(clock() - before))/CLOCKS_PER_SEC;

			//check results
#ifdef DEBUG
			for(k=1; k<n_sizes[i]; ++k) {
				if(temp_array[k-1] > temp_array[k]) {
					printf("\n\n%s failed\n", algorithms[j].name);
					assert(temp_array[k-1] <= temp_array[k]);
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
	for (j=0; j<NUM_ALGS; ++j) {
		len = strlen(algorithms[j].name);
		printf("%*s", ((len > 10) ? len+2 : 10), algorithms[j].name);
	}
	putchar('\n');
	
	for (i=start_n; i<num_n; i++) {
		printf("%10lu", n_sizes[i]);
		for (j=0; j<NUM_ALGS; j++) {
			len = strlen(algorithms[j].name);
			printf("%*.0f", ((len > 10) ? len+2 : 10), table_results[j][i]*1000);
		}
		putchar('\n');
	}


	FILE* file = fopen("output.dat", "w");

	fprintf(file, "%*sN", 11, " ");
	for (i=start_n; i<num_n; ++i)
		fprintf(file, "%12lu", n_sizes[i]);
	fputc('\n', file);

	for (i=0; i<NUM_ALGS; ++i) {
		fprintf(file, "%*s", 12, algorithms[i].name);
		for (j=start_n; j<num_n; ++j)
			fprintf(file, "%*.0f", 12, table_results[i][j]*1000);
		fputc('\n', file);
	}

	fclose(file);


	return 0;
}


