#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

//Implement your functions here
/*
	CREATE GRAPH
	- allocates memory for the graph
	- initializes the members of the structure + arrays
	- returns the newly created graph
*/
GRAPH *createGraph(int vertices){
	// Allocate new Graph 
	GRAPH* G = (GRAPH*)malloc(sizeof(GRAPH));
	G->num_vertices = vertices;
	// Allocate columns
	G->matrix = (int**) malloc(sizeof(int*)*vertices);

	// Create Rows for each column
	for ( int i = 0 ; i < vertices ; i++ ) {
		G->matrix[i] = (int*) malloc(sizeof(int)*vertices);
		// Set each item in the row to 0
		for ( int j = 0 ; j < vertices ; j++ ) {
			G->matrix[i][j] = 0;
		}
	}

	return G;
}


/*
	INSERT EDGE
	- plots the adjacent vertices in the adjacency matrix
*/
void insertEdge(GRAPH *G, int **W, int u, int v, int l, int w){
	// Mark adjacent vertices
	G->matrix[u][v] = l;
	// Update weight
	W[u][v] = w;
}


/*
	CREATE VISITED
	- returns an integer array called visited - allocate and initialize your array properly
	- this will be used in the dijkstra() function to mark visited nodes
	- 1: visited, 0: not visited yet
*/
int *createVisited(GRAPH *G){
	// Allocate visited array
	int* visited = (int*)malloc(sizeof(int)*G->num_vertices);

	for ( int i = 0 ; i < G->num_vertices ; i++ ){
		// Set each cell as not visited
		visited[i] = 0;
	}

	return visited;
}


/*
	CREATE DISTANCE
	- returns an integer array called distance - allocate and initialize your array properly
	- this will be used in the dijkstra() function to keep track of the distance of the vertices
	- initialize to 99999 (maximum distance possible)
*/
int *createDistance(GRAPH *G){
	int* distance = (int*)malloc(sizeof(int)*G->num_vertices);

	for ( int i = 0 ; i < G->num_vertices ; i++ ){
		// Set each cell as max distance
		distance[i] = 99999;
	}

	return distance;
}
int *createWeight(GRAPH *G){
	int* weight = (int*)malloc(sizeof(int)*G->num_vertices);

	for ( int i = 0 ; i < G->num_vertices ; i++ ){
		// Set each cell as max distance
		weight[i] = 0;
	}

	return weight;
}

int** createWeights(int vertices){
	int** weight = (int**)malloc(sizeof(int*)*vertices);
	// Allocate columns

	// Create Rows for each column
	for ( int i = 0 ; i < vertices ; i++ ) {
		weight[i] = (int*) malloc(sizeof(int)*vertices);
		// Set each item in the row to 0
		for ( int j = 0 ; j < vertices ; j++ ) {
			weight[i][j] = 0;
		}
	}

	return weight;
}


/*
	CREATE PARENT
	- returns an integer array dijkstra parent - allocate and initialize your array properly
	- this will be used in the dijisktra() function to keep track of the parent of a visited vertex
	- initialize to -1 (no parent yet)
*/
int *createParent(GRAPH *G){
	int* parent = (int*)malloc(sizeof(int)*G->num_vertices);

	for ( int i = 0 ; i < G->num_vertices ; i++ ){
		// Set each cell as -1 'no parent yet'
		parent[i] = -1;
	}

	return parent;
}

//  Find vertex u where !visited[u] and d[u] is minimum & new weight satisfies the constraint
int getU(int u, int *d, int *v, int len, int *w, int weight_constraint){
	int min = 999999, index = 0;

		for (int i = 0 ; i < len ; i++ ){
			// printf(" u: %i\n",u);
		if ((v[i]!= 1) && (d[i] < min) && ((w[i] + w[u]) <= weight_constraint) ){
			min = d[i];
			index = i;
		}
	}

	return index;
}

/*
	DIJKSTRA
	- implements dijkstra's algorithm to find the shortest path from a source to a target
	- computes for the distance of the path
	- you may create additional functions for the different operations needed in the dijkstra's algorithm
*/
void dijkstra(GRAPH *G, int **W,int source, int target, int weight_constraint){
	
	// Initialize arrays
	int* visited = createVisited(G);
	int* parent = createParent(G);
	int* distance = createDistance(G);
	int* weight = createWeight(G);

	//  set distance of source to 0
	distance[source] = 0;
	int d = 0;
	int w = 0;

	for (int i = 0 ; i < G->num_vertices ; i++){
		//  Find vertex u where !visited[u] and d[u] is minimum
		int u = getU(i, distance, visited, G->num_vertices, weight, weight_constraint);
		printf("| u: %i |\n", u);
				
		// Set vertex a visited
		visited[u] = 1;

		// update distances of unvisited adj vertices
		for (int v = 0 ; v < G->num_vertices ; v++){
			// printf("| %i |\n", G->matrix[u][v]);
			if( (G->matrix[u][v] != 0) && (!visited[v])){
				d = distance[u] + G->matrix[u][v];
				w = weight[u] + W[u][v];
			
				if (d < distance[v]){
					distance[v] = d;
					parent[v] = u;
					weight[v] = w;
				}
			}
		}
	}

	// Get path
	int p = target; 

	printf("DISTANCE FROM %i to %i: %i\n", source+1, target+1, distance[target]);
	printf("PATH FROM %i to %i: ", source+1, target+1);
	
	while (p!= -1){
		printf("%d ", p+1);
		p = parent[p];
	}
	printf("\n");
}

/*
	PRINT MATRIX
	- prints the values of the adjacency matrix
	- follow the layout provided in the sample run
*/
void printMatrix(GRAPH *G){
	for ( int i = 0 ; i < G->num_vertices ; i++ ){
		for( int j = 0 ; j < G->num_vertices ; j++ ){
			// Print each node
			printf("%i  ", G->matrix[i][j]);
		}
		printf("\n");
	}
}


/*
	FREE MATRIX
	- frees the allocated memory for the adjacency matrix
*/
void freeMatrix(GRAPH *G){
	// Free each row
	 for ( int i = 0 ; i < G->num_vertices ; i++ ){
		free(G->matrix[i]);
	 }

	// Free the column
	free(G->matrix);
}

int main() {
	char command;
	int vertices, lines, u, v, w, l,source, target, weight_constraint;


	scanf("%d", &vertices);
	scanf("%d", &weight_constraint);
	scanf("%d", &source);
	scanf("%d", &target);

	GRAPH *G = createGraph(vertices);
	int** WM = createWeights(vertices);

	while(1) {
		scanf(" %c", &command);

		switch(command) {
			case '+':
				scanf(" %d %d %d %d", &u, &v, &l, &w);
				insertEdge(G, WM, u-1, v-1, l, w); //there's a -1 since we use 0-indexing in the arrays
				printf("Successfully inserted edge %d %d | length %d weight %d \n", u, v, l, w);
				break;
			case '#':
				dijkstra(G, WM, source-1, target-1, weight_constraint);
				printf("\n");
				break;
			case 'p':
				printf("\nADJACENCY MATRIX: \n");
				printMatrix(G);
				break;
			case 'f':
				freeMatrix(G);
				break;
			case 'Q':
				free(G);
				return 0;
			default:
				printf("Unknown command: %c\n", command);
		}
	}
}