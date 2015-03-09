double objective_function(int *x, int n)
{
  int val=0;

  // verify the string length constraint

  if (n%5!=0)
    {
      printf("Trap function requires string length divisible by 5.\n");
      exit(-55);
    }
	
  // add up all the traps

  for (int i=0; i<n;)
    {
      int sum=0;

      // compute the sum of bits in the next 5 bits

      for (int k=0; k<5; k++)
	sum+=x[i++];
      
      // compute the trap-5 value for the computed sum

      if (sum==5)
	val+=5;
      else
	val+=4-sum;
    }

  // return the result
  
  return val;
}
