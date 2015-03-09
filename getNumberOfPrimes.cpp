
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
#include <cstddef>
#include <fstream>
#include <string>
#include <algorithm>


using namespace std;
/*
 * Complete the function below.
 */
int getNumberOfPrimes(int N) {

    int sumPrimos=0;
    
       

    for(int number_test = 2; number_test < N ; number_test++){
        for(int divisor = 2; divisor < number_test; divisor++){
            if(number_test % divisor == 0){
                break;
            }
            else if(number_test % divisor != 0){
                // cout << number_test << " ";
                sumPrimos++;
                break;
            }
        }
    }

    cout<< sumPrimos << endl;
 
    
    
    
    
    
    return sumPrimos;

}

int main() {
    ofstream fout(getenv("OUTPUT_PATH"));
    int res;
    int _N;
    cin >> _N;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    res = getNumberOfPrimes(_N);
    fout << res << endl;
    
    fout.close();
    return 0;
}
