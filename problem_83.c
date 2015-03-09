//problem_83.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define N 80

#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _b : _a; })

typedef struct Node{
	int x;
	int y;
	int distance;
	int weight;
	int visited;

}Node;

void init_node(Node* n,int i,int j,int w){
	n->x=i;
	n->y=j;
	n->distance=1000000;
	n->weight=w;
	n->visited=false;
	}

Node grid[N][N];


void update_neighbor(int dx, int dy,Node* u){
	int newy = (u->y) + dy;
	int newx = (u->x) + dx;
	if (newx >= 0 && newy >= 0){
		Node* n = &grid[newx][newy];
		if (!n->visited){
			n->distance = min(n->distance,u->distance + n->weight);
			//printf("  dist(%d,%d)= %d\n",newx,newy,n->distance);
		}
	}
}

/*returns the closest of 4 nodes to node o*/
Node* closest_unvisited(){
	int i,j,min=1000000;
	Node* minNode;
	for (i=0;i<N;i++){
		for (j=0;j<N;j++){
			if (!grid[i][j].visited){
				if (grid[i][j].distance < min){
					min = grid[i][j].distance;
					minNode = &grid[i][j];
				}
			}
		}
	}
	return minNode;
}

int findMinSumPath(){
	Node* u;
	grid[0][0].distance = grid[0][0].weight;
	int i;
	//for (i=0;i<5;i++){
	while (!grid[N-1][N-1].visited){
		u = closest_unvisited();
		u->visited = true;
		printf("u:{%d,%d,%d,%d}\n",u->x,u->y,u->distance,u->weight);
		
		//update neighbors	
		update_neighbor(0,-1,u);
		update_neighbor(0,1,u);
		update_neighbor(1,0,u);
		update_neighbor(-1,0,u);

		
	}
	
	return grid[N-1][N-1].distance;
}

void fillRow(char* line,int i){
	int j=0;
	const char delim[2] = ",";
	char* token = strtok(line,delim);
	init_node(&grid[i][j],i,j,atoi(token));

	while((token = strtok(NULL,delim)) != NULL){
		j++;
		init_node(&grid[i][j],i,j,atoi(token));
	}
}

int main(int argc, char **argv){

	FILE *file=fopen("matrix.in","r");

	if (file!=NULL){
		//printf("no errors opening the file!\n");
		int i;
		for (i=0;i<N;i++){
			char line[N*5];
			fscanf(file,"%s",line);
			fillRow(line,i);
		}

		int minSum = findMinSumPath();

		printf("min path sum: %d\n",minSum);

	}
	else {
		printf("file could not be read!\n");
		return 1;
	}

	fclose(file);	
	return 0;
}
