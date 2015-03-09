#include<iostream>
using namespace std;

int main()
{
  int l, r;
  int ans = 0;
  cin >> l >> r;
  bool flag = false;

  for (int i = 30; i >= 0; i--)
  {
    // cout << " i :" << i << " l: "<< l <<" r: "<< r << endl; 

    int val1 = l & (1 << i);
    int val2 = r & (1 << i);

    // cout << " i : " << i << " val1: "<< val1 << " val2: "<< val2<<endl; 

    if (val1 != val2)
      flag = true;
    if (flag)
      ans |= (1 << i);
  }
  
  cout << " asd" <<  (1 << 0) << " ..."<<endl;

  cout << ans << endl;
  return 0;
}