#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <cmath>

using namespace std;


/*
An iterative mergesort that uses an auxilliary array
of size max(2^floor(log_2(n/2)), n - 2*(2^floor(log_2(n/2)))) to sort the input array.*/
void iterativemerge(int a[],int n)
{
	int t = pow(2,floor(log(n/2)/log(2)));
	int tempsize = max(t,n-2*t); 			//uses a max of n/2 (if n = power of 2)
											//but it uses less as it gets farther away from powers of 2 (less than or greater than)
	int * temparray = new int[tempsize];
	for(int z=0;z<tempsize;z++) temparray[z] = 0;

	int l, l_max, r, r_max, incr, i, j;
	
	incr = 1;
	while(incr<n)
	{
		if(incr>n/2)
		{
			l = 0;
			r = n - incr;
			l_max = r - 1;
			r_max = n - 1;

			for(int b=0;b<n-incr;b++) temparray[b] = a[incr+b];	//save smaller part into temparray 
			for(int b=incr-1;b>=0;b--) a[b+n-incr] = a[b];			//shift larger part to the right
		}
		else
		{
			l = 0;
			r = incr;
			l_max = r-1;
			r_max = (l_max + incr < n) ? l_max + incr : n-1;
		}
		i = j = 0;

		while(i<n)
		{
			if(incr<n/2)
				for(j=0;j<incr && j<=l_max-l;j++) temparray[j] = a[l+j];

			j = 0;
			while(j<incr && j<=l_max-l && r<=r_max)
			{
				if(a[r]<temparray[j])
					a[i] = a[r++];
				else
					a[i] = temparray[j++];

				i++;
			}
			
			while(j<incr && j<=l_max-l)
				a[i++] = temparray[j++];
			while(r<=r_max)
				a[i++] = a[r++];

			l = r;
			r = (r + incr < n)? r+incr : n-1;
			l_max = r-1;
			r_max = (l_max + incr < n) ? l_max + incr : n-1;
		}
		
		incr*=2;
	}

	delete [] temparray;
	return;
}


//Insertion sort
void insertionsort(int a[], int n)
{
	int temp,j;

	for(int i=0;i<n;i++)
	{
		j = i-1;
		temp = a[i];
		while(a[j]>temp and j>=0)
		{
			a[j+1] = a[j];
			j--;
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
   if(l<= heapsize && a[l] > a[i])
      largest = l;
   else largest = i;

   if(r<=heapsize && a[r]>a[largest])
      largest = r;
   
   if(largest!=i)
   {
      temp = a[i];
      a[i] = a[largest];
      a[largest] = temp;
      maxheapify(a, largest, heapsize);
   }
   return;
}

void heapsort(int a[],int n)
{
   int temp;
   int heapsize = n-1;

   for(int i=(n-2)/2;i>=0;i--)
      maxheapify(a,i,heapsize);

   for(int i=n-1;i>0;i--)
   {
      temp = a[0];
      a[0] = a[i];
      a[i] = temp;
      heapsize--;
      maxheapify(a,0,heapsize);
   }
   
	return;
}





/* ternary heapsort and necessary macros/functions */

#define right3(x) (3*(x)+1)
#define middle(x) (3*(x)+2)
#define left3(x) (3*(x)+3)
#define parent3(x) (((x)-1)/3)

void ternaryMaxheapify(int a[], int i, int heapsize)
{
   int largest;
   int temp;

   int l = left3(i);
	int m = middle(i);
   int r = right3(i);
   if(l<= heapsize && a[l] > a[i])
      largest = l;
   else largest = i;

   if(m<=heapsize && a[m]>a[largest])
      largest = m;

	if(r<=heapsize && a[r]>a[largest])
		largest = r;

   if(largest!=i)
   {
      temp = a[i];
      a[i] = a[largest];
      a[largest] = temp;
      ternaryMaxheapify(a, largest, heapsize);
   }
   return;
}

void ternaryHeapsort(int a[],int n)
{
   int temp;
   int heapsize = n-1;

   for(int i=(n-2)/3+1;i>=0;i--)
      ternaryMaxheapify(a,i,heapsize);

   for(int i=n-1;i>0;i--)
   {
      temp = a[0];
      a[0] = a[i];
      a[i] = temp;
      heapsize--;
      ternaryMaxheapify(a,0,heapsize);
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

   for(int j=p;j<r;j++)
   {
      if(a[j] <= x)
      {
         i++;
         temp = a[j];
         a[j] = a[i];
         a[i] = temp;
      }
   }
   temp = a[i+1];
   a[i+1] = x;
   a[r] = temp;
   return i+1;
}

void quicksort(int a[], int p, int r)
{
	if(p < r)
   {
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
   i=0;

   int * a1 = new int[n1];
   int * a2 = new int[n2];

   for(i;i<n1;i++) a1[i] = a[p+i];
   for(i=0;i<n2;i++) a2[i] = a[q+i+1];

   i = j = 0;

   for(int k=p;k<=r;k++)
   {
      if(i==n1)
      {
         a[k] = a2[j];
         j++;
         continue;
      }
      if(j==n2)
      {
         a[k] = a1[i];
         i++;
         continue;
      }
      if(a1[i] <= a2[j])
         a[k] = a1[i++];

      else
         a[k] = a2[j++];

      }
}

void mergesort(int a[], int p, int r)
{
	if(p < r)
   {
      int q = (p+r)/2;
      mergesort(a, p, q);
      mergesort(a, q+1, r);
      merge(a, p, q, r);
   }
}





