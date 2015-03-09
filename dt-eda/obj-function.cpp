/**
   \file obj-function.cpp
   \brief User-defined functions that define the problem.
   \see Example input parameter files: \link example_input \endlink, \link example_input_bisection \endlink, \link example_input_big \endlink
   \see Example objective function (concatenated trap of order 5): \link example-trap5.cpp \endlink
   \see Example function for setting the number of characters in each string position: \link example-num-values.cpp \endlink
*/

#include <stdlib.h>
#include <stdio.h>

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
//! Specifies the objective function to maximize.
/**
   The example included by default is a simple onemax problem, which is
   defined as the sum of all characters in a string (usually binary
   but it can really be used with any alphabet represented by integers
   like here). 

   The objective function is coupled with the function that specifies
   the number of values of all string positions, 
   set_num_vals(int *, int). Both these functions can be found
   in obj-function.cpp.

   \param 
     x input string (candidate solution)
   \param 
     n string length

   \return 
     Value of the objective function for the given candidate solution.
*/

double objective_function(int *x, int n)
{
  int val=0;

  // compute the sum of all values in the given string
  // (works also for non-binary representations)

  for (int i=0; i<n; i++)
    val+=x[i];

  // return the final value
  
  return val;
}


/**
   An additional example of the objective function. Here a concatenated
   trap of order 5 is used, which is fully deceptive. This function
   can be used for binary strings where the number of bits is an integer
   multiple of 5. This function should not be used for non-binary
   representations.

   \example example-trap5.cpp
*/

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
//! Specifies the number of values for different string characters.
/**
   Each string position i has values from 0 to num_values[i]-1. 
   By default, the code makes all string positions ternary (values 0 to 2)
   but alternative assignments can be used.

   \param 
     num_vals array to store the numbers of values for all string positions
   \param
     n string length

   \return 
     No return value.
*/

void set_num_vals(int *num_vals, int n)
{
  // set the number of values for each string position (variable),
  // use 2 for binary, 3 or higher for higher candinality alphabets

  for (int i=0; i<n; i++)
    num_vals[i]=3;
}

/**
   An additional example of specifying the alphabets for all string
   positions. Here the first half of the symbols are binary whereas
   the remaining symbols can contain values from 0 to (n-1) where
   n is the string length. By default, a function that specifies all
   attributes as binary is included in the code.

   \example example-num-values.cpp
*/

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
/** Verify whether the given solution is the global optimum.
    If there is no such function, just return 0 by default. The default
    function works for the default objective function, that is, onemax.

   \param 
     x input string (candidate solution)
   \param 
     n string length
   \param  
     num_vals array of the numbers of values for all string positions

    \return
    0 if the solution is non-optimal, something else if the solution is optimal
*/

int is_optimal(int *x, int n, int *num_vals)
{
  int ok=1;

  for (int i=0; (i<n)&&(ok); i++)
    if (x[i]!=num_vals[i]-1)
      ok=0;

  return ok;
};
