
#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <cstdio>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <string>
#include <cstdio>
#include <limits>
#include <vector>
#include <cstdlib>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;



int main(){

	list<int> *l;
	l =new list<int> [ 10 ];

	l->push_back( 69 );
	// l->insert( 20 );
	// l->insert( 30 );
	// l->insert( 40 );




	cout << l->size() << endl;
	cout << l->empty() << endl;
 
	return 0;
}