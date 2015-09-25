#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdio.h>



/*
An iterative mergesort that uses an auxilliary array
of size max(2^floor(log_2(n/2)), n - 2*(2^floor(log_2(n/2)))) to sort the input array.
uses a max of n/2 (if n = power of 2)
but it uses less as it gets farther away from powers of 2 (less than or greater than)
*/
void iterative_merge(int a[], int n)
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
void insertionsort(int a[], int n)
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



/* Heapsort and necessary macros/functions

*/

#define right(x) (2*(x)+2)
#define left(x) (2*(x)+1)
#define parent(x) (((x)-1)/2)

void maxheapify(int a[], int i, int heapsize)
{
	int largest;
	int temp;

	int l = left(i);
	int r = right(i);
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

void heapsort(int a[], int n)
{
	int temp;
	int heapsize = n-1;

	for (int i=(n-2)/2; i>=0; i--) {
		maxheapify(a, i, heapsize);
	}

	for (int i=n-1; i>0; i--) {
		temp = a[0];
		a[0] = a[i];
		a[i] = temp;
		heapsize--;
		maxheapify(a, 0, heapsize);
	}

	return;
}





/* ternary heapsort and necessary macros/functions */

#define right3(x) (3*(x)+1)
#define middle(x) (3*(x)+2)
#define left3(x) (3*(x)+3)
#define parent3(x) (((x)-1)/3)

void ternary_maxheapify(int a[], int i, int heapsize)
{
	int largest;
	int temp;

	int l = left3(i);
	int m = middle(i);
	int r = right3(i);
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

void ternary_heapsort(int a[], int n)
{
	int temp;
	int heapsize = n-1;

	for(int i=(n-2)/3+1; i>=0; i--) {
		ternary_maxheapify(a, i, heapsize);
	}
	
	for(int i=n-1; i>0; i--) {
		temp = a[0];
		a[0] = a[i];
		a[i] = temp;
		heapsize--;
		ternary_maxheapify(a, 0, heapsize);
	}

	return;
}

/*
Quicksort.  Partion pivots on last element
*/
int partition(int a[], int p, int r)
{
	int x = a[r];
	int i = p-1;
	int temp;

	for (int j=p; j<r; ++j) {
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

void quicksort(int a[], int p, int r)
{
	if (p < r) {
		int q = partition(a,p,r);
		quicksort(a, p, q-1);
		quicksort(a, q+1, r);
	}
}

/*
Recursive Mergesort
*/
void merge(int a[], int p, int q, int r)
{
	int n1 = q - p + 1;
	int n2 = r - q;
	int i,j;
	
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

void mergesort(int a[], int p, int r)
{
	if(p < r) {
		int q = (p+r)/2;
		mergesort(a, p, q);
		mergesort(a, q+1, r);
		merge(a, p, q, r);
	}
}



/*
Iterative Quicksort.  Partion pivots on last element
*/
void iter_quicksort(int a[], int p, int r)
{
	//TODO figure out why 2*ceil(log(r+1)/log(2)) wasn't enough
	int sz = 4*(int)ceil(log(r+1)/log(2.0));

	int* pr = (int*)malloc(sizeof(int) * sz);
	int* pos = pr;
	int x, i, j, temp, pl, rl;
	//printf("pr = %p\n", pr);
	
	pr[0] = p;
	pr[1] = r;
	
	while (pos >= pr) {
		/*
		for (int k=0; k<=r; ++k)
			printf("%d ", a[k]);
		putchar('\n');
		*/

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
		
		
		if (i+1 < rl) {
			pos[0] = i+1;
			pos[1] = rl;
			
			if (pl < i-1) {
				pos += 2;
				pos[0] = pl;
				pos[1] = i-1;
			}
		} else if (pl < i-1) {
			pos[0] = pl;
			pos[1] = i-1;
		} else {
			pos -= 2;
		}
	}
	
	//printf("pr = %p\n", pr);
	free(pr);
}


/*
Quicksort + insertion sort.  Partion pivots on last element
*/

void quick_insertionsort(int a[], int p, int r)
{
	if (p < r) {
		//25 (7150) < 32 (7230) < 16 (7300) < 20 (7360)
		if (r - p < 25) {
			insertionsort(&a[p], r-p+1);
		} else {
			int q = partition(a,p,r);
			quick_insertionsort(a, p, q-1);
			quick_insertionsort(a, q+1, r);
		}
	}
}



