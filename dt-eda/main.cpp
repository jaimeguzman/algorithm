/** 
\mainpage
This program implements an estimation of distribution algorithm 
with dependency tree probabilistic models. The algorithm does not
assume that solutions are binary strings, every string position
can obtain any number of values, wich is specified by the user.

For references and more information on estimation of distribution 
algorithms or dependency tree models, please see the MEDAL report 
published with this code at http://medal.cs.umsl.edu/files/2006010.pdf

All user-defined functions are located in obj-function.cpp, which defines
the objective function, the function to set the numbers of values in 
different string positions, and the function to verify optimality.

Usage: dt-eda [parameter file name] [--help] [--version]

\author 
Martin Pelikan

\date
2006

\version 1.0

\section license License Information

Feel free to use, modify and distribute the code for academic purposes 
with an appropriate acknowledgment of the source, but in all resulting 
publications please include a citation to the following publication:

Martin Pelikan (2006). Implementation of the Dependency-Tree 
Estimation of Distribution Algorithm in C++. MEDAL
Report No. 2006010, Missouri Estimation of Distribution
Algorithms Laboratory, University of Missouri-St. Louis, MO.

*/

/**
   \file main.cpp
   \brief Main function.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bisection.hpp"
#include "eda.hpp"
#include "heap.hpp"
#include "parse-input.hpp"
#include "random.hpp"
#include "tree-model.hpp"

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
/**
   The main function.
*/

int main(int argc, char **argv)
{
  Parameters params;

  // set default parameter values

  params.population_size=300;
  params.problem_size=25;
  params.max_generations=50;
  params.tournament_size=2;
  params.replacement=0;
  params.verbose_mode=0;
  params.quiet_mode=0;
  params.bisection=0;
  params.num_bisection_runs=20;

  // process input arguments

  if (argc>2)
    {
      printf("Expected only one command-line argument.\n");
      exit(-10);
    }
  else
  if (argc==2)
  {
    if ((strcmp(argv[1],"--help")==0)||
	(strcmp(argv[1],"-h")==0)||
	(strcmp(argv[1],"/help")==0)||
	(strcmp(argv[1],"/h")==0)||
	(strcmp(argv[1],"-?")==0)||
	(strcmp(argv[1],"/?")==0))
      {
	// help

	printf("Usage: dt-eda [parameter file name] [--help] [--version]\n\n");
	param_help();
	exit(0);
      }
    else 
    if ((strcmp(argv[1],"--version")==0)||
	(strcmp(argv[1],"-v")==0))
      {
	// version info

	printf("dt-eda-1.0\n");
	exit(0);
      }
    else
      {
	// parameter file

	FILE *f=fopen(argv[1],"r");
	if (f==NULL)
	  {
	    printf("ERROR: Could not open parameter file %s\n",argv[1]);
	    exit(-1);
	  }

	parse_input_file(f,&params);
        printf("Parameter file: %s\n",argv[1]);
      };
  }
  else
    printf("No parameter file: Using default parameters\n");

  // print the parameters

  print_parameters(&params);

  // perform one run of the dependency-tree EDA with the current parameters
  // and user defined functions (parameters from user-defined parameter files 
  // go first)

  if (params.bisection)
    {
      AveragePopulationStatistics avg_stats;

      bisection(&params,&avg_stats);

      print_bisection_summary(stdout,&avg_stats);
    }
  else
    {
      PopulationStatistics stats;

      one_run(&params,&stats);

      print_summary(&stats);
    };

  // get out

  return 0;
}
