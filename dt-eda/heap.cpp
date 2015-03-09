/**
   \file heap.cpp

   Maximum heap used to store edges in Prim's algorithm for (maximum) spanning trees.
*/

#include <stdio.h>

#include "heap.hpp"

#define parent_index(i) ((i-1)/2)
#define left_child_index(i) (1+2*i)

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
//! Build a max-heap for a given array. 

int build_max_heap(int *a, int *b, double *x, int n, int *index, int *rev_index)
{
  // builds a max-heap by max-heapifying all nodes with some children

  for (int i=(n>>1)-1; i>=0; i--)
    max_heapify(x,i,n,index,rev_index);

  // get back

  return n;
};

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
//! Run max-heapify on a specified element of a heap (push down).

int max_heapify(double *x, int i, int n, int *index, int *rev_index)
{
  double this_x=x[index[i]];
  int old_ii=index[i];

  int done=0;
  do {
    int c1=left_child_index(i);
    int c2=c1+1;

    int ic1=index[c1];
    
    if (c2<n)
      {
	int ic2=index[c2];
	
	if (x[ic1]<x[ic2])
	  {
	    ic1=ic2;
	    c1=c2;
	  };
      };
    
    if (x[ic1]>this_x)
      {
	index[i]=index[c1];
	rev_index[index[i]]=i;
	i=c1;
	if (left_child_index(i)>=n)
	  done=1;
      }
    else
      done=1;
    
  } while (!done);
  
  index[i]=old_ii;
  rev_index[index[i]]=i;

  return i;
};

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
//! Increase a given key in the heap.

int increase_key_max_heap(double *x, int i, double val, int n, int *index, int *rev_index)
{
  x[i]=val;
  return float_up_max_heap(x,rev_index[i],n,index,rev_index);
};

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
//! Float up an element up the heap (after increasing its value).

int float_up_max_heap(double *x, int i, int n, int *index, int *rev_index)
{
  double this_x=x[index[i]];
  int old_ii=index[i];

  int parent_idx=parent_index(i);

  while ((i>0)&&(this_x>x[index[parent_idx]]))
    {
      index[i]=index[parent_idx];
      rev_index[index[i]]=i;
      i=parent_idx;
      if (i>0)
	parent_idx=parent_index(i);
    };

  index[i]=old_ii;
  rev_index[index[i]]=i;

  return i;
};

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
//! Pop the maximum (includes the removal of maximum).

int pop_max_heap(double *x, int &n, int *index, int *rev_index)
{
  n--;
  int val=index[0];

  index[0]=index[n];
  rev_index[index[n]]=0;
  max_heapify(x,0,n,index,rev_index);

  return val;
}

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
//! Print the max heap (used mostly for debugging).

void print_max_heap(double *x, int n, int *index, int *rev_index)
{
  for (int i=0; i<n; i++)
    {
      printf("x[%u] = %5.3f (",i,x[index[i]]);
      if (i*2+1<n)
	printf("%5.3f ",x[index[2*i+1]]);
      if (i*2+2<n)
	printf("%5.3f ",x[index[2*i+2]]);
      printf(")\n");
    };
}

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
//! Check the max heap for errors (used mostly in debugging).

int check_max_heap(double *x, int n, int *index, int *rev_index)
{
  int ok=1;

  for (int i=0; (i<n)&&(ok); i++)
    {
      if (i*2+1<n)
	if (x[index[i]]<x[index[2*i+1]])
	  ok=0;

      if (i*2+2<n)
	if (x[index[i]]<x[index[2*i+2]])
	  ok=0;
    };

  if (ok==0)
    printf("not OK\n");
  else
    printf("OK\n");

  return ok;
}
