/**
   \file random.cpp
   \brief Various random number generator related functions based on the basic generator in MT.cpp.
*/

#include <stdio.h>
#include <math.h>

#include "random.hpp"
#include "MT.hpp"

long _Q = _M/_A;     // M / A 
long _R = _M%_A;     // M mod A
long _seed=123;          // a number between 1 and m-1

char whichGaussian=0; // which gaussian to generate

// ================================================================================
//
// name:          drand
//
// function:      returns a floating-point random number generated according to
//                uniform distribution from [0,1)
//
// parameters:    (none)
//
// returns:       (double) resulting random number
//
// ================================================================================

double drand()
{
//   long lo,hi,test;
  
//   hi   = _seed / _Q;
//   lo   = _seed % _Q;
//   test = _A*lo - _R*hi;
  
//   if (test>0)
//     _seed = test;
//   else
//     _seed = test+_M;

//   return double(_seed)/_M;
  return genrand_real2();
}

// ================================================================================
//
// name:          intRand
//
// function:      returns an integer random from [0,max)
//
// parameters:    max..........the upper bound
//
// returns:       (int) resulting random number
//
// ================================================================================

int intRand(int max)
{
//   double r=drand();
//   printf("r=%f\n",r);
  return (int) (drand()*max);
};

// ================================================================================
//
// name:          longRand
//
// function:      returns a long integer random from [0,max)
//
// parameters:    max..........the upper bound
//
// returns:       (long) resulting random number
//
// ================================================================================

long longRand(long max)
{
   return (long) ((double) drand()*max);
};

// ================================================================================
//
// name:          flipCoin
//
// function:      returns 0 or 1 with the same probability
//
// parameters:    (none)
//
// returns:       (int) resulting number
//
// ================================================================================

char flipCoin()
{
  if (drand()<0.5)
      return 1;
  else
      return 0;
};

// ================================================================================
//
// name:          setSeed
//
// function:      sets the random seed
//
// parameters:    seed.........a new random seed
//
// returns:       (long) the result of the operation
//
// ================================================================================

unsigned long  setSeed(unsigned long newSeed)
{
  // set the seed and return the result of the operation
  
  init_genrand(newSeed);

  return newSeed;
};

// ================================================================================
//
// name:          gaussianRandom
//
// function:      returns a number generating acc. to a Gaussian distr. with 
//                a standard deviation std
//
// parameters:    mean...........the mean
//                stddev.........a standard deviation
//
// returns:       (double) the random number
//
// ================================================================================

double gaussianRandom(double mean,double stddev)
{
   double  q,u,v,x,y;

   /*  
      Generate P = (u,v) uniform in rect. enclosing acceptance region 
      Make sure that any random numbers <= 0 are rejected, since
      gaussian() requires uniforms > 0, but RandomUniform() delivers >= 0.
   */
   do {
      do { u=drand(); } while (u==0);
      do { v=drand(); } while (v==0);

      v = 1.7156 * (v - 0.5);

      /*  Evaluate the quadratic form */
      x = u - 0.449871;
      y = fabs(v) + 0.386595;
      q = x * x + y * (0.19600 * y - 0.25472 * x);

      /* Accept P if inside inner ellipse */
      if (q < 0.27597)
         break;

      /*  Reject P if outside outer ellipse, or outside acceptance region */
    } while ((q > 0.27846) || (v * v > -4.0 * log(u) * u * u));

    /*  Return ratio of P's coordinates as the normal deviate */
    return (mean + stddev * v / u);
}

