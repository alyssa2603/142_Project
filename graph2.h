// ___  ____    _  _ ____ ___    ____ ___  _ ___    ___ _  _ _ ____    ____ _ _    ____ 
// |  \ |  |    |\ | |  |  |     |___ |  \ |  |      |  |__| | [__     |___ | |    |___ 
// |__/ |__|    | \| |__|  |     |___ |__/ |  |      |  |  | | ___]    |    | |___ |___ 
//

//Structure for the graph
typedef struct graph_tag {
	int **matrix; //holder of the adjacency matrix
	int num_vertices; //holds the vertex count
    
} GRAPH;

//define MAX_LABELS (this is the maximum number of label a vertex can take)
#define MAX_LABELS 100

typedef struct label{
    int weight;
    int length;
} LABEL;


//Each vertex will have a node label
typedef struct node_label{
    LABEL* labels;
    int * untreated;
    int * treated;
    int label_count;
    int untreated_count;
    int treated_count;
}NODE_LABEL;


/*
	CREATE GRAPH
	- allocates memory for the graph
	- initializes the members of the structure + arrays
	- returns the newly created graph
*/
GRAPH *createGraph(int vertices);


/*
	INSERT EDGE
	- plots the adjacent vertices in the adjacency matrix
*/
void insertEdge(GRAPH *G, int **W, int u, int v, int l, int w);

/*
	PRINT MATRIX
	- prints the values of the adjacency matrix
	- follow the layout provided in the sample run
*/
void printMatrix(GRAPH *G);


/*
	FREE MATRIX
	- frees the allocated memory for the adjacency matrix
*/
void freeMatrix(GRAPH *G, int ** WM);