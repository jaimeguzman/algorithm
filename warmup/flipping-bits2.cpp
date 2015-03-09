
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
 
 
int main() {
    int z;
    cin>>z;
    while(z--)
    {   unsigned long long num;
        cin>>num;    
        cout<<(unsigned long long)pow(2,32)-num-1<<"\n";
    }
    return 0;
}

