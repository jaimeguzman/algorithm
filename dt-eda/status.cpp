/**
   \file status.cpp
   \brief Methods of class Status, which displays text-mode status bars in verbose mode.
*/

#include "status.hpp"

#include <stdio.h>

Status::Status(int n)
{
  last=-1;
  this->n=n;
}

Status::~Status()
{
}

void Status::update(double p)
{
  int i,k;

  k=(int)((double)p*n);

  if (last!=k)
    {
      if (last>=0)
	for (i=0; i<n+2; i++)
	  printf("\b");
      
      printf("[");
      for (i=0; i<k; i++)
	printf("=");
      for (i=n-k; i>0; i--)
	printf("-");
      printf("]");
      fflush(stdout);
      
      last=k;
    };
}

void Status::reset()
{
  last=-1;
}
