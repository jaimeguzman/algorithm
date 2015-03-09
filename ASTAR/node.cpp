#include <iostream>
#include <iomanip>
#include <queue>
#include <string>
#include <math.h>
#include <ctime>


#include <stdio.h>
#include <cstdlib>

using namespace std;

/*
class node
{
	
	private:
		static int valor = 1;
		
	
};
*/


int array[10][10];


void fillArray(){
	
	for(int i=0; i<10; i++)
	{
		for(int j=0; j<10;j++)
		{
			array[i][j]=1;
		}
	}
}


int main(){

	cout << " asdasd "<< endl;
	fillArray();
	
	for( int i=0; i< 10;i++ )
	{
		for(int j=0; j<10;j++)
		{
			cout << array[i][j] <<" ";	
		}cout << endl;
	}
	
return 0;
}
