/**
   \file parse-input.cpp
   \brief Necessary functions for parsing input parameter files.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "parse-input.hpp"
#include "random.hpp"

//! Maximum width of a line to read from parameter file.

#define MAX_LINE_WIDTH 1000

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
//! Parse the input file and store the results in a structure Parameters.
//! \see Example input parameter file: \link example_input \endlink

void parse_input_file(FILE *f, Parameters *params)
{
  if (f==NULL)
    return;

  char id[MAX_LINE_WIDTH];

  int seed_set=0;
  while (get_new_identifier(f,id))
    {
      if (strcmp(id,"population_size")==0)
	get_int_value(f,params->population_size);
      else
      if (strcmp(id,"max_generations")==0)
	get_int_value(f,params->max_generations);
      else
      if (strcmp(id,"problem_size")==0)
	get_int_value(f,params->problem_size);
      else
      if (strcmp(id,"replacement")==0)
	get_int_value(f,params->replacement);
      else
      if (strcmp(id,"tournament_size")==0)
	get_int_value(f,params->tournament_size);
      else
      if (strcmp(id,"bisection")==0)
	get_int_value(f,params->bisection);
      else
      if (strcmp(id,"num_bisection_runs")==0)
	get_int_value(f,params->num_bisection_runs);
      else
      if (strcmp(id,"quiet_mode")==0)
	get_int_value(f,params->quiet_mode);
      else
      if (strcmp(id,"verbose_mode")==0)
	get_int_value(f,params->verbose_mode);
      else
      if (strcmp(id,"random_seed")==0)
	{
	  int seed;
	  get_int_value(f,seed);
	  setSeed(seed);
	  seed_set=1;
	}
      else
	{
	  printf("%s is an unknown identifier\n",id);
	  exit(-1);
	};
    };
  
  if (seed_set==0)
    setSeed(123);
}

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
//! Print a short description of parameters.

void param_help()
{
  printf("List of parameters for input file (you can specify any subset):\n\n");

  printf("  -> Population size:\n      population_size = <number>\n\n");
  printf("  -> Problem size (number of characters):\n      problem_size = <number>\n\n");
  printf("  -> Maximum number of generations:\n      max_generations = <number>\n\n");
  printf("  -> Replacement (0=restricted tournament repl., 1=full repl.):\n      replacement = <number>\n\n");
  printf("  -> Tournament size for tournament selection:\n      tournament_size = <number>\n\n");
  printf("  -> Use bisection to optimize the population size:\n      bisection = <number>\n\n");
  printf("  -> Number of successful runs for optimal population sizing:\n      num_runs=<number>\n\n");
  printf("  -> Quiet mode (prints only the end-of-the-run summary):\n      quiet_mode = <number>\n\n");
  printf("  -> Verbose mode (do not use with redirected output):\n      verbose_mode = <number>\n\n");
  printf("  -> Random seed:\n      random_seed = <number>\n\n");
  printf("See example_input, example_input_bisection, and example_input_big for example input files\n");
}

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
//! Get a new identifier from the file and scan until after next '='.

int get_new_identifier(FILE *f, char *s)
{
  char c=0;
  int n=0;
  int done=0;

  while ((!feof(f))&&(!done))
    {
      c=fgetc(f);
      if (((c>='a')&&(c<='z'))||
	  ((c>='A')&&(c<='Z'))||
	  (c=='_'))
	done=1;
    }

  if (done)
    {
      s[0]=c;
      n=1;
      done=0;
      while ((!feof(f))&&(!done)) 
	{
	  c=fgetc(f);
	  if (((c>='a')&&(c<='z'))||
	      ((c>='A')&&(c<='Z'))||
	      (c=='_'))
	    s[n++]=c;
	  else 
	    done=1;
	};
      s[n]='\0';

      if (c=='=')
	done=1;
      else
	done=0;

      while ((!feof(f))&&(!done))
	{
	  c=fgetc(f);
	  if (c=='=')
	    done=1;
	};
      
      if (!done)
	{
	  printf("Expected '=' after identifier %s\n",s);
	  exit(-1);
	}

      return 1;
    }

  return 0;
}

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
//! Read an integer value from a file.

int get_int_value(FILE *f, int &val)
{
  char line[MAX_LINE_WIDTH];
  fgets(line,MAX_LINE_WIDTH,f);
  sscanf(line,"%u",&val);

  return 1;
}

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
//! Print the parameters to stdout.

int print_parameters(Parameters *params)
{
  printf("Parameters:\n");
  printf("  population_size    = %u\n",params->population_size);
  printf("  problem_size       = %u\n",params->problem_size);
  printf("  max_generations    = %u\n",params->max_generations);
  printf("  tournament_size    = %u\n",params->tournament_size);
  printf("  replacement        = %u\n",params->replacement);
  printf("  bisection          = %u\n",params->bisection);
  printf("  num_bisection_runs = %u\n",params->num_bisection_runs);
  printf("  quiet_mode         = %u\n",params->quiet_mode);
  printf("  verbose_mode       = %u\n",params->verbose_mode);
  separator(stdout);

  return 0;
}

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------


/**
   \example example_input

   An example parameter file for the decision tree EDA.
*/

/**
   \example example_input_bisection

   An example parameter file that uses bisection to determine the optimal population size for 10 successful runs.
*/

/**
   \example example_input_big

   An example parameter file that solves a big problem and has verbose output switched on.
*/
