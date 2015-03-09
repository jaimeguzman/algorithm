void set_num_vals(int *num_vals, int n)
{
  // set the number of values for the first half of the string to 2,
  // while in the remaining positions the number of symbols is n.

  for (int i=0; i<n/2; i++)
    num_vals[i]=2;
  for (int i=n/2+1; i<n; i++)
    num_vals[i]=n;
}
