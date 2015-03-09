/*

Problem Statement

Shashank likes strings in which consecutive characters are different. 
For example, he likes ABABA, while he doesn't like ABAA. 
Given a string containing characters A and B only, 
he wants to change it into a string he likes. To do this,
 he is allowed to delete the characters in the string.

***Your task is to find the minimum number of required deletions.****

Input Format

The first line contains an integer T, i.e. the number of test cases. 
The next T lines contain a string each.

Output Format

***For each test case, print the minimum number of deletions required.

Constraints

1≤T≤10 
1≤ length of string ≤105

*/
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;



int minimumNumberDeletions(string s ){
	int min =0;

	int sLength = s.length();
	int sPrevLength = s.length();
 
	for(int i = 0; i < sLength-1; i++ ){

			if( s[i] == s[i+1]){
				// cout << "s[i]: " << s[i]<< endl;
				for( int j=i+1; j < sLength-1; j++   ){
					// cout <<"s[j] "<< s[j] <<" "<< i << " "<< j << endl;
					s[j] = s[j+1];	
				}
				i--;
				sLength--;
			}
	}


	return (sPrevLength-sLength);
}



int main() {
 
  int t; // number test case
  cin >> t;

  for (int i=0; i<t; i++) {
  	//cada caso

  	string auxString;
  	cin >> auxString;

	// cout << "---- "<< auxString << endl;

  	cout << minimumNumberDeletions(auxString)<< endl;



  }

  return 0;
}

