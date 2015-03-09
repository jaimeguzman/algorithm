/**
   \file tree-model.cpp
   \brief Methods of class TreeModel for working with tree probabilistic models.
*/

#include "heap.hpp"
#include "random.hpp"
#include "status.hpp"
#include "tree-model.hpp"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------

TreeModel::TreeModel(int n)
{
  this->n=n;

  // assume all variables are binary

  num_vals=new int[n];
  for (int i=0; i<n; i++)
    num_vals[i]=2;

  // initialize some variables

  max_num_vals=2;

  mi_num = NULL;
  mi_p = NULL;
  mi_pi = NULL;
  mi_pj = NULL;
  succ = NULL;
  pred = NULL;
  num_succ = NULL;
  anc_order = NULL;
  prob = NULL;
  num_prob = NULL;
}

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------

TreeModel::TreeModel(int n, int *num_vals)
{
  this->n=n;

  // store range of all variables

  this->num_vals=new int[n];
  max_num_vals=0;
  for (int i=0; i<n; i++)
    {
      this->num_vals[i]=num_vals[i];
      if (this->num_vals[i]>max_num_vals)
	max_num_vals=this->num_vals[i];
    }

  // initialize some variables

  mi_num = NULL;
  mi_p = NULL;
  mi_pi = NULL;
  mi_pj = NULL;
  succ = NULL;
  pred = NULL;
  num_succ = NULL;
  anc_order = NULL;
  prob = NULL;
}

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------

TreeModel::~TreeModel()
{
  // free memory used by the range of all variables

  delete[] num_vals;

  if (mi_num)
    delete[] mi_num;
  if (mi_p)
    delete[] mi_p;
  if (mi_pi)
    delete[] mi_pi;
  if (mi_pj)
    delete[] mi_pj;
  if (anc_order)
    delete[] anc_order;
  if (prob)
    {
      for (int i=0; i<n; i++)
	delete[] prob[i];
      delete[] prob;
      delete[] num_prob;
    };

  if (succ)
    {
       for (int i=0; i<n; i++)
         delete[] succ[i];
       delete[] succ;
       delete[] num_succ;
    }

  if (pred)
    delete[] pred; 
}

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------

double TreeModel::mutualInformation(int i, int j, int **x, int N)
{
  int num_vals_i=num_vals[i];
  int num_vals_j=num_vals[j];
  int total_vals=num_vals_i*num_vals_j;

  if (mi_num==NULL)
    {
      int max_val_product=max_num_vals*max_num_vals;
      mi_num=new int[max_val_product];
      mi_p=new double[max_val_product];
      mi_pi=new double[max_num_vals];
      mi_pj=new double[max_num_vals];
    };

  int *num=mi_num;
  double *p=mi_p;
  double *pi=mi_pi;
  double *pj=mi_pj;
  
  double I=0;

  for (int k=0; k<total_vals; k++)
    num[k]=0;

  // compute frequencies of all value combinations

  for (int k=0; k<N; k++)
    {
      int vi=x[k][i];
      int vj=x[k][j];

      num[vi*num_vals_j+vj]++;
    };

  // transform frequencies into probabilities

  for (int k=0; k<total_vals; k++)
    p[k]=(double) num[k]/N;

  // compute marginal probabilities from joints

  for (int vi=0; vi<num_vals_i; vi++)
    pi[vi]=0;

  for (int vj=0; vj<num_vals_j; vj++)
    pj[vj]=0;

  for (int vi=0; vi<num_vals_i; vi++)
    for (int vj=0; vj<num_vals_j; vj++)
      {
	double d=p[vi*num_vals_j+vj];
	pi[vi]+=d;
	pj[vj]+=d;
      };

  // compute mutual information from all the probabilities

  for (int vi=0; vi<num_vals_i; vi++)
    for (int vj=0; vj<num_vals_j; vj++)
      {
	int pos=vi*num_vals_j+vj;
	double pp=p[pos];
	
	double d=(pp<1E-10)? 1:(pp/(pi[vi]*pj[vj]));
	
	I+=pp*log(d);
      };

  // return the resulting mutual information

  return I;
}

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------

void TreeModel::learnStructure(int **x, int N, int loud)
{
  int i,j,k;

  // initialize the complete graph with I(i,j) weight on each edge (i,j)

  int num_edges=n*(n-1)/2;

  int *a=new int[num_edges];
  int *b=new int[num_edges];
  int *index=new int[num_edges];
  int *rev_index=new int[num_edges];
  int *selected=new int[n];

  Status *status = new Status();

  if (pred==NULL)
    pred=new int[n];

  double *weights = new double[num_edges];
  double *I = new double[num_edges];

  if (num_succ==NULL)
    num_succ=new int[n];

  int num_selected=0;
  int last_selected=-1;
  int last_predecessor=-1;
  int heap_size=0;

  if (loud)
    printf("   learning model structure\n");

  // initialize variables

  for (i=0; i<n; i++)
    {
      selected[i]=0;
      num_succ[i]=0;
    }

  // create the tree

  if (loud)
    {
      printf("      phase 1/2: ");
      status->reset();
      status->update(0);
    };

  for (i=1,k=0; i<n; i++)
    {
      for (j=0; j<i; j++,k++)
	{
	  a[k]=j;
	  b[k]=i;
	  weights[k]=HEAP_MINUS_INFINITY;
	  I[k]=mutualInformation(j,i,x,N);
	  index[k]=k;
	  rev_index[k]=k;
	};

      if (loud)
	status->update(((double)1.0*k)/num_edges);
    };

  if (loud)
    printf("\n");

  // build the initial heap

  build_max_heap(a,b,weights,num_edges,index,rev_index);
  heap_size=num_edges;

  // a random node is first selected (last_selected stores its index)

  last_selected = intRand(n);
  last_predecessor = -1;
  pred[last_selected]=-1;
  root = last_selected;

  // initialize the status bar

  if (loud)
    {
      printf("      phase 2/2: ");
      status->reset();
      status->update(0);
    };

  // we continue until all nodes have been selected

  while (num_selected<n)
    {
      selected[last_selected]=1;
      pred[last_selected]=last_predecessor;
      num_selected++;
      if (loud)
	status->update(((double) 1.0*num_selected)/n);
      
      if (last_predecessor>=0)
	num_succ[last_predecessor]++;

      // relax neighbors and find a new node to select (if not done)

      if (num_selected<n)
	{

	  for (i=0; i<last_selected; i++)
	    {
	      int this_index=last_selected*(last_selected-1)/2+i;
	      if (I[this_index]>weights[this_index])
		increase_key_max_heap(weights,this_index,I[this_index],heap_size,index,rev_index);
	    };
	  
	  for (i=last_selected+1; i<n; i++)
	    {
	      int this_index=i*(i-1)/2+last_selected;
	      if (I[this_index]>weights[this_index])
		increase_key_max_heap(weights,this_index,I[this_index],heap_size,index,rev_index);
	    };
	  
	  do {
	    i=pop_max_heap(weights,heap_size,index,rev_index);
	  } while ((selected[a[i]])&&(selected[b[i]]));

	  if (!selected[a[i]])
	    {
	      last_selected=a[i];
	      last_predecessor=b[i];
	    }
	  else
	    {
	      last_selected=b[i];
	      last_predecessor=a[i];
	    };
	};
    };
  if (loud)
    printf("\n");

  // create the actual graph

  if (succ==NULL)
    succ=new int*[n];
  else
    for (i=0; i<n; i++)
      if (succ[i])
	delete[] succ[i];
  
  for (int i=0; i<n; i++)
    if (num_succ[i]>0)
      {
	succ[i]=new int[num_succ[i]];
	num_succ[i]=0;
      }
    else
      succ[i]=NULL;

  for (int i=0; i<n; i++)
    if (pred[i]>=0)
      {
	int p=pred[i];

	succ[p][num_succ[p]++]=i;
      }; 

  // compute the ancestral ordering

  if (anc_order==NULL)
    anc_order=new int[n];

  int count=0;
  anc_order[count]=root;
  ancestralOrderingRec(count);

  // free memory

  delete[] a;
  delete[] b;

  delete[] weights;
  delete[] selected;
  delete[] index;
  delete[] rev_index;

  delete[] I;
  delete status;
};

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------

void TreeModel::printModel(FILE *f)
{
  printf("\n-------------------------------------------------------------------------------\n");
  printf("Structure:\n");
  for (int i=0; i<n; i++)
    {
      printf("   %u",i);
      if (num_succ[i]>0)
	{
	  printf(" ->");
	  for (int j=0; j<num_succ[i]; j++)
	    printf(" %u",succ[i][j]);
	};
      printf("\n");
    };

  printf("Probabilities:\n");
  for (int i=0; i<n; i++)
    {
      printf("   %2u: ",i);
      for (int j=0; j<num_prob[i]; j++)
	printf("%4.2f ",prob[i][j]);
      printf("\n");
    };
  printf("\n-------------------------------------------------------------------------------\n");
}

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------

void TreeModel::ancestralOrderingRec(int &i)
{
  int node=anc_order[i];
  int j;

  for (j=0; j<num_succ[node]; j++)
    {
      anc_order[++i]=succ[node][j];
      ancestralOrderingRec(i);
    };
}

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------

void TreeModel::learnProbabilities(int **x, int N, int loud)
{
  int i,j;
  Status *status=new Status();

  if (loud)
    printf("   learning model parameters\n");

  if (prob==NULL)
    {
      prob=new double*[n];
      num_prob=new int[n];
    }
  else
    for (i=0; i<n; i++)
      if (prob[i])
	delete[] prob[i];

  if (loud)
    printf("      phase 1/1: ");

  for (i=0; i<n; i++)
    {
      if (loud)
	status->update(((double)i)/n);

      if (pred[i]<0)
	{
	  int k=num_vals[i];
	  prob[i]=new double[k];
	  num_prob[i]=k;
	  for (j=0; j<k; j++)
	    prob[i][j]=0;

	  for (j=0; j<N; j++)
	    prob[i][x[j][i]]+=1;
	  for (j=0; j<k; j++)
	    prob[i][j]=prob[i][j]/N;
	}
      else
	{
	  int k=num_vals[i]*num_vals[pred[i]];
	  prob[i]=new double[k];
	  num_prob[i]=k;
	  for (j=0; j<k; j++)
	    prob[i][j]=0;

	  int *total=new int[num_vals[pred[i]]];
	  for (j=0; j<num_vals[pred[i]]; j++)
	    total[j]=0;

	  for (j=0; j<N; j++)
	    {
	      int idx=num_vals[pred[i]]*x[j][i]+x[j][pred[i]];
	      prob[i][idx]+=1;
	      total[x[j][pred[i]]]++;
	    };

	  for (j=0; j<k; j++)
	    {
	      int pred_value=j%num_vals[pred[i]];
	      prob[i][j]=prob[i][j]/total[pred_value];
	    };

	  delete[] total;
	}
    }
  
  if (loud)
    {
      status->update(1);
      printf("\n");
    };

  delete status;
}

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------

void TreeModel::sampleModel(int **x, int N)
{
  int i,j;

  for (i=0; i<N; i++)
    {
      int idx=anc_order[0];
      x[i][idx]=generate_marginal(num_vals[idx],prob[idx]);
      for (j=1; j<n; j++)
      {
	int idx=anc_order[j];

	// printf("can use max i=%u\n",num_prob[idx]);

	x[i][idx]=generate_conditional(num_vals[idx],num_vals[pred[idx]],prob[idx],x[i][pred[idx]]);
      }
    }
}

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------

int TreeModel::generate_marginal(int n, double *p)
{
  int i=0;
  double d=drand();
  double sum=p[i++];

  while (sum<d)
    sum+=p[i++];

  return (i-1);
}

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------

int TreeModel::generate_conditional(int n, int m, double *p, int pred)
{
  int i=pred;
  double d=drand();
  double sum=p[i];

  while (sum<d)
    {
      i+=m;
      sum+=p[i];

      if (i>=n*m)
	{
	  printf("Error: generate_conditional outside array bounds...\n");
	  exit(-1);
	}
    }

  return (i/m);
}
