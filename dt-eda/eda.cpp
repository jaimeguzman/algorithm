/**
   \file eda.cpp
   \brief EDA-specific functions (except for the model-related ones).
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "eda.hpp"
#include "random.hpp"
#include "obj-function.hpp"
#include "stats.hpp"
#include "tree-model.hpp"


// Functional type to use for replacement method.

typedef int ReplacementMethod(int **x, 
			      int **y, 
			      int n, 
			      int N, 
			      double *fx, 
			      double *fy);

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
//! Generate a random population of individuals (uniform distribution).

int generate_population(int **x, int n, int N, int *num_vals=NULL)
{
  int i,j;

  // general all variables uniformly randomly
  // (if the numbers of values is not supplied, assumes binary)

  if (num_vals==NULL)
    for (i=0; i<n; i++)
      for (j=0; j<N; j++)
	x[j][i]=(drand()<0.5)? 0:1;
  else
    for (i=0; i<n; i++)
      for (j=0; j<N; j++)
	x[j][i]=intRand(num_vals[i]);

  // return the number of generated individuals
  
  return N;
}

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
//! Generate a poulation full of blocks of 0s and 1s. Only for debugging.

int generate_BB_population(int **x, int n, int N, int k)
{
  int i,j,l;

  // generate a population full of 000..0 and 111..1 building blocks
  // (used for testing the model building procedure, unnecessary for
  // practical applications)

  for (i=0; i<N; i++)
    for (j=0; j<n;)
      {
	int val=(drand()<0.5)? 0:1;
	
	for (l=0; l<k; l++)
	  x[i][j++]=val;
    };

  // return the number of generated individuals

  return N;
}

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
//! Allocate memory for a new population of specified parameters. 

int **allocate_population(int n, int N)
{
  int i;
  int **x;

  // allocate a population as a 2-dimensional int-array

  x=new int*[N];
  for (i=0; i<N; i++)
    x[i]=new int[n];

  // return the allocated array

  return x;
}

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
//! Free memory occupied by a population of specified parameters.

void free_population(int **x, int n, int N)
{
  int i;

  // free memory used by the population

  for (i=0; i<N; i++)
    delete[] x[i];

  delete[] x;
}

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
//! Evaluate a population using the user-specified objective function.

int evaluate_population(int **x, double *f, int n, int N, long &num_evals)
{
  // evaluate all individuals, one by one

  for (int i=0; i<N; i++)
    f[i]=objective_function(x[i],n);

  // increase the number of evaluations

  num_evals+=N;

  // return the number of evaluated individuals

  return N;
}

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
//! Tournament selection with replacement (k-ary tournaments).

int tournament_selection(int **y, int **x, double *f, int n, int N, int k)
{
  int i,j;

  for (i=0; i<N; i++)
    {
      // select a winner of k tournaments (with replacement)

      int winner=intRand(N);
      for (j=1; j<k; j++)
	{
	  int l=intRand(N);
	  if (f[l]>f[winner])
	    winner=l;
	};

      // the winner takes the next spot in the selected population

      for (int ii=0; ii<n; ii++)
	y[i][ii]=x[winner][ii];
    };

  // return the number of selected individuals

  return N;
}

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
//! Print the population to the specified file.

void print_population(FILE *f, int **x, int n, int N)
{
  int i,j;
  
  for (i=0; i<N; i++)
    {
      for (j=0; j<n; j++)
	fprintf(f,"%u",x[i][j]);
      fprintf(f,"   %f\n",objective_function(x[i],n));
    };
}

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
//! Restricted tournament replacement (Harik, 1995) for niching.

int restricted_tournament_replacement(int **x, int **y, int n, int N, double *fx, double *fy)
{
  int i,j;

  // use default value for window size

  int windowSize=(n<N/20)? n:(N/20);

  // for every individual, do the same

  for (i=0; i<N; i++)
    {
      // select a random subset from the original population (window) and 
      // find the most similar guy to the new individual in this window
      // (string Hamming distance)

      int pick=intRand(N);
      int dist=individual_distance(x[i],y[pick],n);

      for (j=1; j<windowSize; j++)
	{
	  int pick2=intRand(N);
	  int dist2=individual_distance(x[i],y[pick2],n);

	  if (dist2<dist)
	    {
	      pick=pick2;
	      dist=dist2;
	    }
	}

      // if the most similar guy from the window is better than the new guy,
      // the new guy replaces it

      if (fx[i]<fy[pick])
	{
	  memcpy(x[i],y[pick],sizeof(x[i][0])*n);
	  fx[i]=fy[pick];
	}
    }

  // return the number of processed new individuals

  return N;
}

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
//! Replace the entire old population with the new population.

int full_replacement(int **x, int **y, int n, int N, double *fx, double *fy)
{
  int i;

  // just replace entire old population with the new guys

  for (i=0; i<N; i++)
    {
      memcpy(x[i],y[i],sizeof(x[i][0])*n);
      fx[i]=fy[i];
    }

  // return the number of processed new individuals

  return N;
}

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
//! Compute a distance between two individuals (number of non-matching chars).

int individual_distance(int *x, int *y, int n)
{
  int i;
  int d=0;

  for (i=0; i<n; i++)
    if (x[i]!=y[i])
      d++;

  return d;
}

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
//! Execute one run of a decision-tree EDA with the specified parameters.

int one_run(Parameters *params, PopulationStatistics *stats)
{
  int N=params->population_size;
  int n=params->problem_size;
  int max_generations=params->max_generations;

  int **current_population;
  int **selected_population;
  int **sampled_population;

  double *current_f;
  double *sampled_f;

  int *num_vals = new int[n];

  // allocate populations and necessary fitness arrays

  current_population = allocate_population(n,N);
  selected_population = allocate_population(n,N);
  sampled_population = allocate_population(n,N);
  
  current_f = new double[N];
  sampled_f = new double[N];

  // initialize the replacement method

  ReplacementMethod *replacement;
  if (params->replacement==0)
    replacement=restricted_tournament_replacement;
  else
    if (params->replacement==1)
      replacement=full_replacement;
    else
      {
	printf("ERROR: Unknown replacement method (%u)\n",params->replacement);
	exit(-2);
      };

  // initialize the number of values

  set_num_vals(num_vals,n);

  // generate initial population

  generate_population(current_population,n,N,num_vals);

  // evaluate initial population

  evaluate_population(current_population,current_f,n,N,stats->num_evals);

  // initialize some main-loop variables

  int done=0;
  int t=0;

  // init the statistics and print the initial status information

  init_population_statistics(stats);
  compute_population_statistics(current_population,current_f,n,N,num_vals,stats);
  
  if (params->quiet_mode==0)
    print_status(t,stats);
  else
    params->verbose_mode=0;

  // main loop

  while (!done)
    {
      // increment generation counter

      t++;

      // selection

      tournament_selection(selected_population,
			   current_population,
			   current_f,
			   n,
			   N,
			   params->tournament_size);

      // variation

      variation(sampled_population,selected_population,params,num_vals);

      // evaluation of new candidates
      
      evaluate_population(sampled_population,sampled_f,n,N,stats->num_evals);
      
      // replacement
      
      replacement(current_population,
		  sampled_population,
		  n,
		  N,
		  current_f,
		  sampled_f);

      // statistics

      compute_population_statistics(current_population,current_f,n,N,num_vals,stats);

      // print current status

      if ((params->quiet_mode==0)&&(params->bisection==0))
	print_status(t,stats);

      // should terminate?

      if ((t>max_generations)||(stats->success==1))
	done=1;
    }

  // free memory

  delete[] num_vals;
  delete[] sampled_f;
  delete[] current_f;

  free_population(current_population,n,N);
  free_population(selected_population,n,N);
  free_population(sampled_population,n,N);

  // return with success/failure (0/1)

  return stats->success;
}

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
//! Variation operator of the decision-tree EDA (learns and samples model).

int variation(int **sampled_population,int **selected_population, Parameters *params, int *num_vals)
{
  int N=params->population_size;
  int n=params->problem_size;
  int loud=params->verbose_mode;

  if (loud)
    separator(stdout,0);

  TreeModel *t = new TreeModel(n, num_vals);
 
  // learn the model structure and model parameters

  t->learnStructure(selected_population,N,loud);
  t->learnProbabilities(selected_population,N,loud);

  // sample the learned model to generate new candidate solutions

  t->sampleModel(sampled_population,N);

  // free memory

  delete t;

  // return the number of generated individuals

  return N;
}


// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
//! Print the status of the algorithm.

void print_status(int t, PopulationStatistics *stats)
{
  printf("Generation: %u\n",t);
  printf("   min:  %f\n",stats->minF);
  printf("   max:  %f\n",stats->maxF);
  printf("   mean: %f\n",stats->avgF);
  separator(stdout);
}

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
//! Print a sequence of dashes to separate text output

void separator(FILE *f, int type)
{
  if (type==0)
    fprintf(f,"- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
  else
    fprintf(f,"---------------------------------------------------------------------------\n");
}

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
//! Print summary of a run.

void print_summary(PopulationStatistics *stats)
{
  printf("Summary:\n");
  printf("   status       = %s\n",(stats->success)? "success":"failure");
  printf("   best_found   = %f\n",stats->maxF);
  printf("   num_evals    = %lu\n",stats->num_evals);
  printf("   pop_size     = %u\n",stats->population_size);
  printf("   problem_size = %u\n",stats->problem_size);
}
