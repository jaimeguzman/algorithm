/**
   \file eda.hpp
   \brief Header file for eda.cpp.
*/

#ifndef _PARAMETERS_HPP_
#define _PARAMETERS_HPP_

#include <stdio.h>

#include "stats.hpp"

//! %Parameters for the decision-tree EDA (can be set using parameter files).

typedef struct {
  int population_size;    //!< Population size
  int problem_size;       //!< Number of variables (string positions)
  int max_generations;    //!< Maximum number of iterations
  int tournament_size;    //!< Size of tournaments
  int replacement;        //!< Replacement method (RTR=0, full=1)
  int bisection;          //!< Optimize population size using bisection (must run many runs)?
  int num_bisection_runs; //!< Number of successful runs for optimal population sizing with bisection.
  int quiet_mode;         //!< Quiet mode?
  int verbose_mode;       //!< Verbose mode?
} Parameters;

int generate_population(int **x, int n, int N);
int **allocate_population(int n, int N);
void free_population(int **x, int n, int N);
int evaluate_population(int **x, double *f, int n, int N);
int tournament_selection(int **y, int **x, double *f, int n, int N, int k);
void print_population(FILE *f, int **x, int n, int N);
int restricted_tournament_replacement(int **y, 
				      int **x, 
				      int n, 
				      int N, 
				      double *fx, 
				      double *fy);
int full_replacement(int **y, int **x, int n, int N, double *fx, double *fy);
int individual_distance(int *x, int *y, int n);
int variation(int **sampled_population,int **selected_population, Parameters *params, int *num_vals);
void print_status(int t, PopulationStatistics *stats);
void print_summary(PopulationStatistics *stats);
int one_run(Parameters *params, PopulationStatistics *stats);

int generate_BB_population(int **x, int n, int N, int k);
void separator(FILE *f, int type=1);

#endif
