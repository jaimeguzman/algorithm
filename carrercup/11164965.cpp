/*
http://www.careercup.com/question?id=11164965


Convert an array "a1 a2 a3...an b1 b2 b3...bn c1 c2 c3...cn" to "a1b1c1 a2b2c2...anbncn", inplace.

*/

#include <string>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <array>

using namespace std; 


int main( ){

	vector<string> lista = {"a1", "a2", "a3", "a4","b1","b2","b3","b4","c1","c2","c3","c4" };
	cout << "Hola mundo " << endl;

	cout << "Elemento en la posición cero "<<lista.at(0) << "-- \n ";

	string primero = lista.at(1);


	cout << " primero " << primero.at(1)<< endl;


/*
			std::string strAux = n.at(1);

				cout << " __" << strAux<<endl; 

*/

	int count = 0;

	for (auto n : lista) {

			string str = (string)n;

			cout << str.at(1) << "..." << endl;

	        if( (count % 2) == 0){
	        // cout << n << " \n ";	        	
	        }


	       	count++; 
	    }


	return 0;
}


