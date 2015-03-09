

#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <cstdlib>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;


/*problem:

Problem Statement

Given two integers, L and R, find the maximal values of A xor B, where A and B satisfy the following condition:

L ≤ A ≤ B ≤ R
Input Format

The input contains two lines; L is present in the first line and R in the second line.

Constraints 
1≤L≤R≤103

Output Format

The maximal value as mentioned in the problem statement.


*/
/*
 * Complete the function below.
 */

vector<int> convert(int x) {
  vector<int> ret;
  while(x) {
    if (x&1)
      ret.push_back(1);
    else
      ret.push_back(0);
    x>>=1;  
  }
  reverse(ret.begin(),ret.end());
  return ret;
}


int maxXor(int l, int r) {
/*

 seudo:
 		- hacer un vector para cada bit  para L y R
		- Recorrerlos y hacer comparaciones 
		- Si son distintos es igual a 1 la salida
		- E caso contrario 0
*/
	
	vector <int>left = convert( l );
	
	for(int i=0; i< left.size(); i++  ){
		
		cout << "valor de n "<< left[i] << endl;	
	}
	
	
	
	
	return 0;
}

int main() {
    int res;
    int _l;
    cin >> _l;
    
    int _r;
    cin >> _r;
    
    res = maxXor(_l, _r);
    cout << res;
    
    return 0;
}