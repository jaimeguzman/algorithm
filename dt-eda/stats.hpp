/**
   \file stats.hpp
   \brief Header file for stats.cpp.
*/

#ifndef _STATS_HPP_
#define _STATS_HPP_

//! Basic population statistics (single run).

typedef struct {
  // fitness statistics
  double minF; int idx_minF;
  double maxF; int idx_maxF;
  double avgF; 

  // number of evaluations
  long int num_evals;
  
  // successful completion
  int success;

  // population size 
  int population_size;

  // problem size
  int problem_size;
} PopulationStatistics;

//! Population statistics for a set of runs.

typedef struct {
  // fitness statistics
  double avg_minF; 
  double avg_maxF; 
  double avg_avgF; 

  double min_minF; 
  double max_maxF; 

  // number of evaluations
  double avg_num_evals;
  
  // successful completion
  double p_success;

  // population size 
  int population_size;

  // problem size
  int problem_size;

  // number of runs
  int num_runs;
} AveragePopulationStatistics;

void init_population_statistics(PopulationStatistics *stats);
int compute_population_statistics(int **x, double *f, int n, int N, int *num_vals, PopulationStatistics *stats);
int average_population_statistics(AveragePopulationStatistics *avg, PopulationStatistics *stats, int num_runs);

#endif
