/**
   \file bisection.cpp
   \brief Bisection method that computes near optimal population size.
*/

#include "bisection.hpp"
#include "eda.hpp"
#include "stats.hpp"

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
//! Bisection method for determining optimal population size.

void bisection(Parameters *params, AveragePopulationStatistics *avg_stats)
{
  AveragePopulationStatistics current_avg_stats;
  Parameters *current_params = new Parameters;
  int result;
  int quiet=params->quiet_mode;

  params->quiet_mode=1;
  params->verbose_mode=0;

  // make the first set of runs

  *current_params = *params;
  result=do_runs(current_params,&current_avg_stats,quiet);
  
  int minN=0;
  int maxN=0;

  if (result)
    {
      // if successful, try to halve population size until failure

      *avg_stats=current_avg_stats;

      while (result)
	{
	  current_params->population_size/=2;
	  result=do_runs(current_params,&current_avg_stats,quiet);

	  if (result)
	    *avg_stats=current_avg_stats;
	};
      
      // set initial population size bounds

      minN=current_params->population_size;
      maxN=minN*2;
    }
  else
    {
      // if failure, double population size until success

      while (!result)
	{
	  current_params->population_size*=2;
	  result=do_runs(current_params,&current_avg_stats,quiet);

	  if (result)
	    *avg_stats=current_avg_stats;
	};
      
      // set initial population size bounds

      maxN=current_params->population_size;
      minN=maxN/2;
    }

  // perform bisection until interval width is at most 5% of the
  // lower bound

  while ((((double)maxN-minN)/minN)>0.05)
    {
      // try to make a set of runs in the middle of the interval

      current_params->population_size=(minN+maxN)/2;
      result=do_runs(current_params,&current_avg_stats,quiet);

      if (result)
	*avg_stats=current_avg_stats;

      // success goes halves the interval downwards, failure upwards

      if (result)
	maxN=current_params->population_size;
      else
	minN=current_params->population_size;
    }

  if (quiet==0)
    {
      printf("Finished bisection with N=%u\n",avg_stats->population_size);
      separator(stdout);
    };

  delete current_params;
}

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
//! Run a number of successful runs, terminate on a failure.

int do_runs(Parameters *params, AveragePopulationStatistics *avg_stats, int quiet)
{
  PopulationStatistics *stats = new PopulationStatistics[params->num_bisection_runs];
  int run;
  int failed=0;
  
  for (run=0; (run<params->num_bisection_runs)&&(!failed); run++)
    {
      int result=one_run(params,&stats[run]);
      failed=!result;
    };
  
  if (quiet==0)
    printf("bisection -> %2u / %2u successes with N=%u\n",
	   run,params->num_bisection_runs,params->population_size);
  
  average_population_statistics(avg_stats,stats,params->num_bisection_runs);

  delete[] stats;

  if (failed)
    return 0;
  else
    return 1;
}

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
//! Print summary of a set of runs (represented by average statistics).

void print_bisection_summary(FILE *f, AveragePopulationStatistics *stats)
{
  fprintf(f,"Bisection summary output:\n");
  fprintf(f,"   num_runs        = %u\n",stats->num_runs);
  fprintf(f,"   avg_best_found  = %f\n",stats->avg_maxF);
  fprintf(f,"   avg_num_evals   = %f\n",stats->avg_num_evals);
  fprintf(f,"   pop_size        = %u\n",stats->population_size);
}
