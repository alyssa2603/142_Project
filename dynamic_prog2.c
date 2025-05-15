#include <stdio.h>
#include <stdlib.h>
#include "graph2.h"


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


void insertEdge(GRAPH *G, int **W, int u, int v, int l, int w){
	// Mark adjacent vertices
	G->matrix[u][v] = l;
	// Update weight
    //there is a weight matrix
	W[u][v] = w;
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

int is_dominated(int old_weight, int old_length, int new_weight, int new_length) 
{
    if((old_weight <= new_weight) && (old_length <= new_length))
    {
        if(old_weight != new_weight || old_length != new_length)
            return 1;
    }
    return 0;
}

/*
	LABEL_SETTING algorithm
*/



//MERONG WEIGHT MATRIX NANDUN LAHAT NG WEIGHT NG BAWAT EDGE
void label_setting(GRAPH *G, int **W,int source, int target, int weight_constraint)
{

    //STEP 0 of the algorithm - INITIALIZE EVERYTHING
    NODE_LABEL *all_labels = (NODE_LABEL*)malloc(sizeof(NODE_LABEL) * G->num_vertices);

    for (int i = 0; i < G->num_vertices; i++) {
        // Pre-allocate arrays with fixed size MAX_LABELS
        all_labels[i].labels = (LABEL*)malloc(MAX_LABELS * sizeof(LABEL));
        all_labels[i].untreated = (int*)malloc(MAX_LABELS * sizeof(int));
        all_labels[i].treated = (int*)malloc(MAX_LABELS * sizeof(int));
        
        // Initialize counts
        all_labels[i].label_count = 0;
        all_labels[i].untreated_count = 0;
        all_labels[i].treated_count = 0;
    }

    all_labels[source].labels[0].length = 0;
    all_labels[source].labels[0].weight = 0;
    all_labels[source].label_count++;
    all_labels[source].untreated[0] = 0;
    all_labels[source].untreated_count++;
    

    //ito yung parang dijkstra's but we expand kasi lahat ngayon ng label ay may sarili nang parent
    // lahat ng vertex ay may sariling vertex and label parent list para matrack ang bawat pinanggalingan ng bawat label
    //set all parent matrix to track kung saan nanggaling ang isang created label
    //malalagay dito ay selected vertex
    int ** vertex_parent_tracker = (int **) malloc(G->num_vertices * sizeof(int *));
    //malalagay dito ay selected label
    int ** label_parent_tracker = (int **) malloc(G->num_vertices * sizeof(int *));

    for (int i = 0; i<G->num_vertices; i++)
    {
        vertex_parent_tracker[i] = (int *) malloc(MAX_LABELS * sizeof(int));
        label_parent_tracker[i] = (int *) malloc(MAX_LABELS * sizeof(int));

        //this is exactly like dijkstra's -1 muna lahat ng parent :)
        for (int j=0; j<MAX_LABELS; j++)
        {
            vertex_parent_tracker[i][j] = -1;
            label_parent_tracker[i][j] = -1;
        }
    }

    //STEP 1 AND 2 ARE INCLOSED IN A WHILE(1) loop only breaks if there are no more untreated labels

    while(1)
    {
        //STEP 1: SELECT LABEL TO BE TREATED FROM UNTREATED VERTICES
        int min_weight = 99999;
        int current_i = -1; //current vertex being treated
        int current_k = -1; //current label of vertex being treated
        //iterate over all vertices
        for(int i = 0; i<G->num_vertices; i++)
        {     
            //iterate over all untreated labels ng vertex i
            for (int j =0; j<all_labels[i].untreated_count; j++)
            {
                int k = all_labels[i].untreated[j]; //candidate label, not yet selected
                //ang constraint dito ay weight as implemented by the algorithm 
                if(all_labels[i].labels[k].weight < min_weight)
                {
                    min_weight = all_labels[i].labels[k].weight;
                    current_i = i;
                    current_k = k;
                }
            }
        }

        //break the loop if walang napiling vertex or label
        //this means na hindi nag-iterate sa untreated labels across all vertices
        if(current_i == -1 || current_k == -1)
            break;

        //STEP 2: TREAT THE LABELS
        //sa lahat ng outgoing edge ng current_i
        //mark as treated agad para ma-update yung untreated count
        all_labels[current_i].treated[all_labels[current_i].treated_count] = current_k;

        all_labels[current_i].treated_count++;

        for (int i = 0; i<all_labels[current_i].untreated_count; i++){
            if (all_labels[current_i].untreated[i] == current_k)
            {
                for(int j = i; j<all_labels[current_i].untreated_count - 1; j++)
                {
                    all_labels[current_i].untreated[j] = all_labels[current_i].untreated[j+1];
                }
                all_labels[current_i].untreated_count--;
                break;
            }
        }
        int currentk_w = all_labels[current_i].labels[current_k].weight;
        int currentk_l = all_labels[current_i].labels[current_k].length;


        for(int i = 0; i<G->num_vertices; i++)
        {
            if(G->matrix[current_i][i] != 0)
            {
                int edge_length = G->matrix[current_i][i];
                int edge_weight = W[current_i][i];

                //check natin if inadd ko ba ang edge na ito sa label na ito, madodominate ba sya
                //ng any other label for this outgoing vertex
                int new_w = currentk_w + edge_weight;
                int new_l = currentk_l + edge_length;


                //dont check for dominance if hindi na talaga pwede itong label na ito
                if(new_w> weight_constraint)
                    continue;
                
                int dom_flag = 0;
                for (int k = 0; k<all_labels[i].label_count; k++)
                {
                    if(is_dominated(all_labels[i].labels[k].weight, all_labels[i].labels[k].length, new_w, new_l))
                    {
                        dom_flag = 1;
                        break;
                    }
                }
                if(!dom_flag)
                {
                    //add this outgoing label to the set of labels 
                    all_labels[i].labels[all_labels[i].label_count].length = new_l;
                    all_labels[i].labels[all_labels[i].label_count].weight = new_w;
                    
                    //itong label na newly added ay hindi pa treated!
                    all_labels[i].untreated[all_labels[i].untreated_count] = all_labels[i].label_count;
                    all_labels[i].untreated_count++;
                    vertex_parent_tracker[i][all_labels[i].label_count] = current_i;
                    label_parent_tracker[i][all_labels[i].label_count] = current_k;

                    all_labels[i].label_count++;
                }

            }
        }
    }

    //ALGORITHM IS OVER HANAPIN ANG PINAKAMAGANDANG LABEL SA TARGET
    //ITO AY YUNG LABEL NA MAY PINAKAMAUNTING COST
    int min_length = 99999;
    int selected_label = -1;
    for(int i = 0; i< all_labels[target].label_count; i++)
    {
        if(all_labels[target].labels[i].length < min_length)
        {
            min_length = all_labels[target].labels[i].length;
            selected_label = i;
        }
    }

    //HANAPIN ANG PARENT NITONG LABEL NA NAPILI

    if(selected_label == -1)
    {
        printf("No path found \n");
        return;
    }

    int p = target; 
    int l = selected_label;

	printf("DISTANCE FROM %i to %i: %i\n", source+1, target+1, min_length);
	printf("PATH FROM %i to %i: ", source+1, target+1);
	
	while (p != -1) {
       printf("%d ", p+1);
        int next_p = vertex_parent_tracker[p][l];
        int next_l = label_parent_tracker[p][l];
        p = next_p;
        l = next_l;
    }
	printf("\n");


    for (int i = 0; i<G->num_vertices; i++)
    {
        free(all_labels[i].labels);
        free(all_labels[i].treated);
        free(all_labels[i].untreated);
    }

    free(all_labels);

    for(int i = 0; i<G->num_vertices; i++)
    {
        free(label_parent_tracker[i]);
        free(vertex_parent_tracker[i]);
    }

    free(label_parent_tracker);
    free(vertex_parent_tracker);
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
void freeMatrix(GRAPH *G, int** WM){
	// Free each row
	 for ( int i = 0 ; i < G->num_vertices ; i++ ){
		free(G->matrix[i]);
	 }

	// Free the column
	free(G->matrix);

    for(int i = 0; i<G->num_vertices; i++)
    {
        free(WM[i]);
    }

    free(WM);
}

int main() {
	char command;
	int vertices, lines, u, v, w, l,source, target, weight_constraint;


	scanf("%d", &vertices);
	scanf("%d", &weight_constraint);
	scanf("%d", &source);
	scanf("%d", &target);

	GRAPH *G = createGraph(vertices);

    //this is the weight matrix
	int** WM = createWeights(vertices);

	while(1) {
		scanf(" %c", &command);

		switch(command) {
			case '+':
				scanf(" %d %d %d %d", &u, &v, &l, &w);
				insertEdge(G, WM, u-1, v-1, l, w); //there's a -1 since we use 0-indexing in the arrays
				// printf("Successfully inserted edge %d %d | length %d weight %d \n", u, v, l, w);
				break;
			case '#':
                
				label_setting(G, WM, source-1, target-1, weight_constraint);
				printf("\n");
				break;
			case 'p':
				printf("\nADJACENCY MATRIX: \n");
				printMatrix(G);
				break;
			case 'f':
				freeMatrix(G, WM);
				break;
			case 'Q':
				free(G);
				return 0;
			default:
				printf("Unknown command: %c\n", command);
		}
	}
}