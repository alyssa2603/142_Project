#include <stdio.h>
#include <stdlib.h>

// Structure for the graph
typedef struct graph_tag {
	int **matrix; 
	int num_vertices;
} GRAPH;

// Structure for the shortest weight-constrained path
typedef struct vertex_tag {
	int* path;
    int vertex_count;
	int length;
} NODE;

// Create Graph
GRAPH *createGraph(int vertices) {
	GRAPH* G = (GRAPH*)malloc(sizeof(GRAPH));
	G->num_vertices = vertices;
	G->matrix = (int**)malloc(sizeof(int*) * vertices);
	for (int i = 0; i < vertices; i++) {
		G->matrix[i] = (int*)malloc(sizeof(int) * vertices);
		for (int j = 0; j < vertices; j++) {
			G->matrix[i][j] = 0;
		}
	}
	return G;
}

// Create Matrix of Weights
int **createWeightMatrix(int vertices) {
	int **weights_matrix = (int**)malloc(sizeof(int*) * vertices);
	for (int i = 0; i < vertices; i++) {
		weights_matrix[i] = (int*)malloc(sizeof(int) * vertices);
		for (int j = 0; j < vertices; j++) {
			weights_matrix[i][j] = 0;
		}
	}
	return weights_matrix;
}

// Directed edge insertion
void insertEdge(GRAPH *G, int** weights, int u, int v, int length, int weight) {
	G->matrix[u][v] = length;
	weights[u][v] = weight;
}

// Create Visited Array
int *createVisited(int vertices) {
	int* visited = (int*)malloc(sizeof(int) * vertices);
	for (int i = 0; i < vertices; i++) {
		visited[i] = 0;
	}
	return visited;
}

void dfs(GRAPH *G, int **weights, int current, int destination, int weight_constraint, int current_weight, int current_length,
    int *visited, int *path, int path_index, NODE* CURRENT_SHORTEST) {
    
	/*
		For Tracking the path: Track the shortest path that satisfies the weight constraint
	*/

    // If current vertex is the destination vertex
	if (current == destination) {
        //  and if the current weight satisfies the constraint and is smaller than the current minimum length
		if (current_weight <= weight_constraint && current_length < CURRENT_SHORTEST->length) {
			CURRENT_SHORTEST->length = current_length;
			CURRENT_SHORTEST->vertex_count = path_index;
            // Make the current path the shortest path
			for (int i = 0; i < path_index; i++) {
				CURRENT_SHORTEST->path[i] = path[i];
			}
		}
		return;
	}


	/*
		DFS Recursive calls
	*/

    // Mark node as visited
	visited[current] = 1;

	for (int i = 0; i < G->num_vertices; i++) {
        // For every unvisited adjacent node
		if (G->matrix[current][i] > 0 && !visited[i]) {
			int n_weight = current_weight + weights[current][i];
			int n_length = current_length + G->matrix[current][i];
			path[path_index] = i;
			// Explore the branch
			dfs(G, weights, i, destination, weight_constraint, n_weight, n_length, visited, path, path_index + 1, CURRENT_SHORTEST);
		}
	}

    // Mark as unvisited (Backtrack)
	visited[current] = 0;
}

void swcp(GRAPH *G, int** weights, int start, int destination, int weight_constraint) {
	int *visited = createVisited(G->num_vertices);
	int *path = (int*)malloc(sizeof(int) * G->num_vertices);
    
    // Tracking the current shortest path
    NODE* CURRENT_SHORTEST = (NODE*)malloc(sizeof(NODE));
    CURRENT_SHORTEST->path = (int*)malloc(sizeof(int) * G->num_vertices);
	CURRENT_SHORTEST->length = 999999999;
    CURRENT_SHORTEST->vertex_count = 0;

    path[0] = start; // Start dfs at starting vertex
	dfs(G, weights, start, destination, weight_constraint, 0, 0, visited, path, 1, CURRENT_SHORTEST);

    // If there was no path found
	if (CURRENT_SHORTEST->vertex_count == 0) {
		printf("\nNO PATH\n");
	} else {
		printf("\nPath: ");
        // Print all vertices in the shortest weight-constrained path
		for (int i = 0; i < CURRENT_SHORTEST->vertex_count; i++) {
			printf("%d ", CURRENT_SHORTEST->path[i] + 1);
		}
        printf("\nLength: %d \n", CURRENT_SHORTEST->length);
	}

	free(visited);
	free(path);
	free(CURRENT_SHORTEST->path);
    free(CURRENT_SHORTEST);
}

// Print adjacency matrix
void printMatrix(GRAPH *G) {
	for (int i = 0; i < G->num_vertices; i++) {
		for (int j = 0; j < G->num_vertices; j++) {
			printf("%i\t", G->matrix[i][j]);
		}
		printf("\n");
	}
}

// Free memory
void freeMatrix(GRAPH *G, int **WM) {
	// Free the graph matrix
	for (int i = 0; i < G->num_vertices; i++) {
		free(G->matrix[i]);
	}
	free(G->matrix);

	// Free the weight matrix
	for (int i = 0; i < G->num_vertices; i++) {
		free(WM[i]);
	}
	free(WM);
}

int main() {
	char command;
	int vertices, start, end, weight_constraint;
	int u, v, length, weight;

	scanf("%d", &vertices);
	scanf("%d", &weight_constraint);
	scanf("%d", &start);
	scanf("%d", &end);

	GRAPH *G = createGraph(vertices);
	int **weights = createWeightMatrix(vertices);

	printf("\nStart: %d \nDestination: %d \nWeight-Constraint: %d\n", start, end, weight_constraint);
	printf("\n\n");

	while (1) {
		scanf(" %c", &command);

		switch (command) {
			case '+':
				scanf(" %d %d %d %d", &u, &v, &length, &weight);
				insertEdge(G, weights, u-1, v-1, length, weight);
				// printf("Successfully inserted edge %d -> %d | length: %d weight: %d\n", u, v, length, weight);
				break;
			case '#':
				printf("\n\n==== SHORTEST WEIGHT-CONSTRAINED PATH ====");

				swcp(G, weights, start-1, end-1, weight_constraint);

				printf("\n");
				break;
			case 'p':
				printf("\nADJACENCY MATRIX: \n");
				printMatrix(G);
				break;
			case 'f':
				freeMatrix(G, weights);
				break;
			case 'Q':
                free(G);
				return 0;
			default:
				printf("Unknown command: %c\n", command);
		}
	}
}
