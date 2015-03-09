/**
   \file stats.cpp
   \brief Functions for computing basic population statistics.
*/


#include "obj-function.hpp"
#include "stats.hpp"

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
//! Compute basic population statistics like the maximum, mean, etc.

int compute_population_statistics(int **x, double *f, int n, int N, int *num_vals, PopulationStatistics *stats)
{
  // store population size and problem size

  stats->population_size=N;
  stats->problem_size=n;

  // compute basic fitness statistics

  stats->idx_minF = stats->idx_maxF = 0;
  stats->minF = stats->maxF = stats->avgF = f[0];

  for (int i=1; i<N; i++)
    {
      stats->avgF+=f[i];

      if (f[i]>stats->maxF)
	{
	  stats->maxF=f[i];
	  stats->idx_maxF=i;
	}
      else
	if (f[i]<stats->minF)
	  {
	    stats->minF=f[i];
	    stats->idx_minF=i;
	  }
    }

  stats->avgF/=N;

  // check whether we found the optimum

  if (is_optimal(x[stats->idx_maxF],n,num_vals))
    stats->success=1;

  // get back

  return 0;
}

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
//! Initialize the population statistics structure.

void init_population_statistics(PopulationStatistics *stats)
{
  stats->num_evals=0;
  stats->minF=stats->maxF=stats->avgF=0;
  stats->idx_minF=stats->idx_maxF=-1;
  stats->success=0;
}

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
//! Compute averages of population statistics over multiple runs.

int average_population_statistics(AveragePopulationStatistics *avg, PopulationStatistics *stats, int num_runs)
{
  // initialize the average stats

  avg->avg_minF=stats[0].minF;
  avg->avg_maxF=stats[0].maxF;
  avg->avg_avgF=stats[0].avgF;
  avg->avg_num_evals=stats[0].num_evals;

  avg->min_minF=stats[0].minF;
  avg->max_maxF=stats[0].maxF;

  avg->population_size=stats[0].population_size;
  avg->problem_size=stats[0].problem_size;
  avg->num_runs=num_runs;

  // do the homework

  for (int run=1; run<num_runs; run++)
    {
      avg->avg_minF+=stats[run].minF;
      avg->avg_maxF+=stats[run].maxF;
      avg->avg_avgF+=stats[run].avgF;
      avg->avg_num_evals+=stats[run].num_evals;

      if (stats[run].minF<avg->min_minF)
	avg->min_minF=stats[run].minF;

      if (stats[run].maxF>avg->max_maxF)
	avg->max_maxF=stats[run].maxF;
    }

  avg->avg_minF/=num_runs;
  avg->avg_maxF/=num_runs;
  avg->avg_avgF/=num_runs; 
  avg->avg_num_evals/=num_runs;

  // return the number of processed runs

  return num_runs;
}
