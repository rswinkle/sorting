#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdio.h>



// An iterative mergesort that uses an auxilliary array
// of size max(2^floor(log_2(n/2)), n - 2*(2^floor(log_2(n/2)))) to sort the input array.
// uses a max of n/2 (if n = power of 2)
// but it uses less as it gets farther away from powers of 2 (less than or greater than)
void iterative_merge(int a[], size_t n)
{

	int t = pow(2, floor(log(n/2)/log(2)));
	int tempsize = (t > n-2*t) ? t : n-2*t;
	int* temparray = (int*)malloc(tempsize*sizeof(int));
	memset(temparray, 0, tempsize*sizeof(int));

	int l, l_max, r, r_max, incr, i, j, cpy_size;
	
	incr = 1;
	while (incr < n) {
		if (incr <= n/2) {
			l = 0;
			r = incr;
			l_max = r-1;
			r_max =  l_max + incr;

		} else {
			/*
 			this case can only happen once and won't happen at all if n is power of 2
			these numbers seem reversed (smaller left over section would be on the right
			except, below, we shift the larger left side to the right so the smaller section becomes
			the "left"
			*/
			l = 0;
			r = n - incr;
			l_max = r - 1;
			r_max = n - 1;

			/*save smaller part into temparray and shift larger part to right */
			memcpy(temparray, &a[incr], (n-incr)*sizeof(int));
			memmove(&a[n-incr], &a[0], incr*sizeof(int));
		}
		
		i = j = 0;

		while (i < n) {
			if (incr <= n/2) {
				cpy_size = l_max - l + 1; //always <= incr
				memcpy(temparray, &a[l], cpy_size*sizeof(int));
			}
			
			j = 0;
			while (j <= l_max-l && r <= r_max) {
				if (a[r] < temparray[j]) {
					a[i] = a[r++];
				} else {
					a[i] = temparray[j++];
				}
				
				++i;
			}
			
			while (j <= l_max-l) {
				a[i++] = temparray[j++];
			}
			while (r <= r_max) {
				a[i++] = a[r++];
			}
			
			l = r;
			r = (r + incr < n)? r+incr : n-1;
			l_max = r-1;
			r_max = (l_max + incr < n) ? l_max + incr : n-1;
		}
		
		incr *= 2;
	}

	free(temparray);
	return;
}


//Insertion sort
void insertionsort(int a[], size_t n)
{
	int temp,j;

	for (int i=1; i<n; ++i) {
		j = i-1;
		temp = a[i];
		
		while (j >= 0 && a[j] > temp) {
			a[j+1] = a[j];
			--j;
		}
		a[j+1] = temp;
	}

	return;
}


// Heapsort and necessary macros/functions
#define right(x) (2*(x)+2)
#define left(x) (2*(x)+1)
#define parent(x) (((x)-1)/2)

void maxheapify(int a[], size_t i, size_t heapsize)
{
	size_t largest;
	int temp;

	size_t l = left(i);
	size_t r = right(i);
	if (l <= heapsize && a[l] > a[i]) {
		largest = l;
	} else {
		largest = i;
	}

	if (r <= heapsize && a[r] > a[largest]) {
		largest = r;
	}

	if (largest != i) {
		temp = a[i];
		a[i] = a[largest];
		a[largest] = temp;
		maxheapify(a, largest, heapsize);
	}
	return;
}

void heapsort(int a[], size_t n)
{
	int temp;
	size_t heapsize = n-1;
	size_t i;

	for (i=(n-2)/2; i>0; --i) {
		maxheapify(a, i, heapsize);
	}
	maxheapify(a, i, heapsize);

	for (i=n-1; i>0; --i) {
		temp = a[0];
		a[0] = a[i];
		a[i] = temp;
		--heapsize;
		maxheapify(a, 0, heapsize);
	}

	return;
}




// ternary heapsort and necessary macros/functions
#define right3(x) (3*(x)+3)
#define middle(x) (3*(x)+2)
#define left3(x) (3*(x)+1)
#define parent3(x) (((x)-1)/3)

void ternary_maxheapify(int a[], size_t i, size_t heapsize)
{
	size_t largest;
	int temp;

	size_t l = left3(i);
	size_t m = middle(i);
	size_t r = right3(i);
	if (l <= heapsize && a[l] > a[i]) {
		largest = l;
	} else {
		largest = i;
	}

	if (m <= heapsize && a[m] > a[largest]) {
		largest = m;
	}

	if (r <= heapsize && a[r] > a[largest]) {
		largest = r;
	}

	if (largest != i) {
		temp = a[i];
		a[i] = a[largest];
		a[largest] = temp;
		ternary_maxheapify(a, largest, heapsize);
	}
	return;
}

void ternary_heapsort(int a[], size_t n)
{
	int temp;
	size_t heapsize = n-1;
	size_t i;

	for(i=(n-2)/3; i>0; --i) {
		ternary_maxheapify(a, i, heapsize);
	}
	ternary_maxheapify(a, i, heapsize);
	
	for(i=n-1; i>0; --i) {
		temp = a[0];
		a[0] = a[i];
		a[i] = temp;
		--heapsize;
		ternary_maxheapify(a, 0, heapsize);
	}

	return;
}


// quad heapsort and necessary macros/functions
#define right4(x) (4*(x)+4)
#define left4(x) (4*(x)+1)
#define parent4(x) (((x)-1)/4)

void quad_maxheapify(int a[], size_t i, size_t heapsize)
{
	size_t largest;
	int temp;

	size_t l = left4(i);
	size_t r = right4(i);

	largest = i;
	for (size_t j=l; j<=heapsize && j<=r; ++j) {
		if (a[j] > a[largest])
			largest = j;
	}

	if (largest != i) {
		temp = a[i];
		a[i] = a[largest];
		a[largest] = temp;
		quad_maxheapify(a, largest, heapsize);
	}
	return;
}

void quad_heapsort(int a[], size_t n)
{
	int temp;
	size_t heapsize = n-1;
	size_t i;

	for(i=(n-2)/4; i>0; --i) {
		quad_maxheapify(a, i, heapsize);
	}
	quad_maxheapify(a, i, heapsize);
	
	for(size_t i=n-1; i>0; --i) {
		temp = a[0];
		a[0] = a[i];
		a[i] = temp;
		--heapsize;
		quad_maxheapify(a, 0, heapsize);
	}

	return;
}


// Quicksort.  Partion pivots on last element
size_t partition(int a[], size_t p, size_t r)
{
	int x = a[r];
	size_t i = p-1;
	int temp;

	for (size_t j=p; j<r; ++j) {
		if (a[j] <= x) {
			++i;
			//use memmove here
			temp = a[j];
			a[j] = a[i];
			a[i] = temp;
		}
	}

	++i;
	//and memmove here to make a stable sort
	temp = a[i];
	a[i] = x;
	a[r] = temp;
	return i;
}

void quicksort(int a[], size_t p, size_t r)
{
	if (p < r && ~r) {
		size_t q = partition(a,p,r);
		quicksort(a, p, q-1);
		quicksort(a, q+1, r);
	}
}


// Generic Quicksort.  Partion pivots on last element
int generic_partition(void* array, size_t p, size_t r, size_t size, int(*compare)(const void*, const void*))
{
	unsigned char* a = (unsigned char*)array;
	unsigned char* x = &a[r*size];
	size_t i = p-1;
	int temp, k;
	unsigned char* ptr1, *ptr2;

	for (size_t j=p; j<r; ++j) {
		if (compare(&a[j*size], x) <= 0) {
			++i;

			k = size;
			ptr1 = &a[j*size];
			ptr2 = &a[i*size];
			while (k >= sizeof(int)) {
				temp = *(int*)ptr1;
				*(int*)ptr1 = *(int*)ptr2;
				*(int*)ptr2 = temp;
				k -= sizeof(int);
				ptr1 += sizeof(int);
				ptr2 += sizeof(int);
			}
			while (k) {
				temp = *ptr1;
				*ptr1 = *ptr2;
				*ptr2 = temp;
				--k;
				++ptr1;
				++ptr2;
			}
		}
	}

	++i;
	k = size;
	ptr1 = &a[i*size];
	while (k >= sizeof(int)) {
		temp = *(int*)ptr1;
		*(int*)ptr1 = *(int*)x;
		*(int*)x = temp;
		k -= sizeof(int);
		ptr1 += sizeof(int);
		x += sizeof(int);
	}
	while (k) {
		temp = *ptr1;
		*ptr1 = *x;
		*x = temp;
		--k;
		++ptr1;
		++x;
	}
	return i;
}

void generic_qsort_recurse(void* a, size_t p, size_t r, size_t size, int(*compare)(const void*, const void*))
{
	if (p < r && ~r) {
		int q = generic_partition(a, p, r, size, compare);
		generic_qsort_recurse(a, p, q-1, size, compare);
		generic_qsort_recurse(a, q+1, r, size, compare);
	}
}

void generic_qsort(void* a, size_t n, size_t size, int(*compare)(const void* , const void*))
{
	generic_qsort_recurse(a, 0, n-1, size, compare);
}

// same as above except uses memcpy

int generic_mcpy_partition(void* array, size_t p, size_t r, size_t size, int(*compare)(const void*, const void*))
{
	unsigned char* a = (unsigned char*)array;
	unsigned char* x = &a[r*size];
	size_t i = p-1;
	int temp;

	for (size_t j=p; j<r; ++j) {
		if (compare(&a[j*size], x) <= 0) {
			++i;

			memcpy(&temp, &a[j*size], size);
			memcpy(&a[j*size], &a[i*size], size);
			memcpy(&a[i*size], &temp, size);
		}
	}

	++i;
	memcpy(&temp, &a[i*size], size);
	memcpy(&a[i*size], x, size);
	memcpy(x, &temp, size);
	return i;
}

void generic_mcpy_qsort_recurse(void* a, size_t p, size_t r, size_t size, int(*compare)(const void*, const void*))
{
	if (p < r && ~r) {
		int q = generic_mcpy_partition(a, p, r, size, compare);
		generic_mcpy_qsort_recurse(a, p, q-1, size, compare);
		generic_mcpy_qsort_recurse(a, q+1, r, size, compare);
	}
}

void generic_mcpy_qsort(void* a, size_t n, size_t size, int(*compare)(const void* , const void*))
{
	generic_mcpy_qsort_recurse(a, 0, n-1, size, compare);
}




// Traditional Recursive Mergesort
void merge(int a[], size_t p, size_t q, size_t r)
{
	size_t n1 = q - p + 1;
	size_t n2 = r - q;
	size_t i,j;
	
	int * a1 = (int*)malloc(n1*sizeof(int));
	int * a2 = (int*)malloc(n2*sizeof(int));

	memcpy(a1, &a[p], n1*sizeof(int));
	memcpy(a2, &a[q+1], n2*sizeof(int));

	i = j = 0;

	for (int k=p; k<=r; ++k) {
		if (i == n1) {
			a[k] = a2[j];
			++j;
			continue;
		}
		if (j == n2) {
			a[k] = a1[i];
			++i;
			continue;
		}
		if (a1[i] <= a2[j]) {
			a[k] = a1[i++];
		} else {
			a[k] = a2[j++];
		}
	}
	
	free(a1);
	free(a2);
}

void mergesort(int a[], size_t p, size_t r)
{
	if (p < r) {
		size_t q = p + ((r - p) / 2);
		mergesort(a, p, q);
		mergesort(a, q+1, r);
		merge(a, p, q, r);
	}
}


// Iterative Quicksort.  Partion pivots on last element
void iter_quicksort(int a[], size_t p, size_t r)
{
	//TODO figure out why 2*ceil(log(r+1)/log(2)) wasn't enough
	int sz = 4*(int)ceil(log(r+1)/log(2.0));

	size_t* pr = (size_t*)malloc(sizeof(size_t) * sz);
	size_t* pos = pr;
	size_t i, j, pl, rl, test;
	int x, temp;
	//printf("pr = %p\n", pr);
	
	pr[0] = p;
	pr[1] = r;
	
	while (pos >= pr) {
		pl = pos[0];
		rl = pos[1];
		
		x = a[rl];
		i = pl-1;

		for (j=pl; j<rl; ++j) {
			if (a[j] <= x) {
				++i;
				temp = a[j];
				a[j] = a[i];
				a[i] = temp;
			}
		}
		++i;
		temp = a[i];
		a[i] = x;
		a[rl] = temp;
		
		test = i-1;
		if (i+1 < rl) {
			pos[0] = i+1;
			pos[1] = rl;
			
			if (pl < test && ~test) {
				pos += 2;
				pos[0] = pl;
				pos[1] = test;
			}
		} else if (pl < test && ~test) {
			pos[0] = pl;
			pos[1] = test;
		} else {
			pos -= 2;
		}
	}
	
	free(pr);
}

// Quicksort + insertion sort.  Partion pivots on last element
void quick_insertionsort(int a[], size_t p, size_t r)
{
	if (p < r && ~r) {
		//25 (7150) < 32 (7230) < 16 (7300) < 20 (7360)
		if (r - p < 25) {
			insertionsort(&a[p], r-p+1);
		} else {
			size_t q = partition(a,p,r);
			quick_insertionsort(a, p, q-1);
			quick_insertionsort(a, q+1, r);
		}
	}
}



