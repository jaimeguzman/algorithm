
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
#include <string>
#include <algorithm>


using namespace std;


/*

Input Format

The first line contains 2 space separated integers 
which is the position of the PacMan. 
The second line contains 2 space separated integers 
which is the position of the food. 
The third line of the input contains 2 space 
separated integers indicating the size of the rows 
and columns respectively. The largest grid size is 30x30.

This is followed by row (r) lines each containing column (c) characters. 
A wall is represented by the character '%' ( ascii value 37 ), 
PacMan is represented by UpperCase alphabet 'P' ( ascii value 80 ), 
empty spaces which can be used by PacMan for movement is represented
by the character '-' ( ascii value 45 ) and food 
is represented by the character '.' ( ascii value 46 )
*/

int is_explored(int x, int y, int explored[100][2], int explored_size);

void nextMove(int x, int y, int pacman_x, int pacman_y, int food_x, int food_y, char grid[30][30]){
    
    //the explored
    int explored[1000][2] = {0};
	    explored[0][0] = pacman_x;
	    explored[0][1] = pacman_y;
    int explored_size = 1; 

    //the path
    int path[1000][2] = {0};
	    path[0][0] = pacman_x;
	    path[0][1] = pacman_y; 
    int path_size = 1;

    // 2 - log the path pointer
    int stack[100][3] 	= {0};
    int stack_size 		= 0;

    //actual position
    int current_x = pacman_x;
    int current_y = pacman_y;

    do{
        // case UP
        if (current_x - 1 >= 0){
            if ((!is_explored(current_x - 1, current_y, explored, explored_size)) 
            	&& grid[current_x - 1][current_y] != '%'){
                stack[stack_size][0] = current_x - 1;
                stack[stack_size][1] = current_y;
                stack[stack_size][2] = path_size;
                stack_size++;
            }
        }
        // case LEFT
        if (current_y - 1 >= 0){
            if ((!is_explored(current_x, current_y - 1, explored, explored_size)) 
            	&& grid[current_x][current_y - 1] != '%'){
                stack[stack_size][0] = current_x;
                stack[stack_size][1] = current_y - 1;
                stack[stack_size][2] = path_size;
                stack_size++;
            }
        }
        
        // case RIGHT
        if (current_y + 1 < y){
            if ((!is_explored(current_x, current_y + 1, explored, explored_size)) 
            	&& grid[current_x][current_y + 1] != '%'){
                stack[stack_size][0] = current_x;
                stack[stack_size][1] = current_y + 1;
                stack[stack_size][2] = path_size;
                stack_size++;
            }
        }
        // case DOWN
        if (current_x + 1 < x){
            if ((!is_explored(current_x + 1, current_y, explored, explored_size)) 
            	&& grid[current_x + 1][current_y] != '%'){
                stack[stack_size][0] = current_x + 1;
                stack[stack_size][1] = current_y;
                stack[stack_size][2] = path_size;
                stack_size++;
            }
        }

        while (is_explored(stack[stack_size - 1][0], stack[stack_size - 1][1], explored, explored_size))
            stack_size--;
	        path_size = stack[stack_size - 1][2];
	        path[path_size][0] = stack[stack_size - 1][0];
	        path[path_size][1] = stack[stack_size - 1][1];
	        explored[explored_size][0] = path[path_size][0];
	        explored[explored_size][1] = path[path_size][1];
	        explored_size++;
	        path_size++;
	        stack_size--;

	        current_x = path[path_size - 1][0];
	        current_y = path[path_size - 1][1];

    } while (current_x != food_x || current_y != food_y);
    
    cout << explored_size <<endl;
    for (int i = 0; i < explored_size; ++i)
        cout<< explored[i][0] << " "<< explored[i][1] <<endl;

    cout << (path_size - 1) << endl;

    for (int i = 0; i < path_size; ++i)
        cout << path[i][0]<<" "<< path[i][1] <<endl;
}

int is_explored(int x, int y, int explored[100][2], int explored_size){
    for (int i = explored_size - 1; i >= 0; i--)
        if (explored[i][0] == x && explored[i][1] == y)
            return 1;
    return 0;
}


int printTablero(char tablero[30][30],int rows,int columns){
	for(int i=0; i< rows; i++){
		for(int j=0; j< columns; j++ ){
			cout << tablero[i][j] << " ";
		}
		cout<<endl;
	}

	return 0;
}


int main(){

	int posPacmanX,posPacmanY;
	int posFoodX,posFoodY;
	int rows,R, columns,C;

	cin >> posPacmanX;	cin >> posPacmanY;
	cin >> posFoodX; 	cin >> posFoodY;
	cin >> rows;		cin >> columns;
	
	R=rows; C=columns;

	char tablero[ 30 ][ 30 ];


	// cout << posPacmanX 	<< " ___ "	<< posPacmanY<<endl;
	// cout << posFoodX 	<< " --- "<< posFoodY<<endl;	
	// cout << rows 		<< " ___ "	<< columns <<endl;
	// cout << "valor de R "<< R<< " ";
	// cout << "valor de C "<< C<<endl;


	for( int i = 0; i < rows ; i++ ){

		scanf("%s[^\\n]%*c", tablero[i]);
	}

	// printTablero( tablero,rows,columns );

	nextMove( rows, columns, posPacmanX, 
				posPacmanY, posPacmanX, posPacmanY, tablero);
	

	return 0;
}


















