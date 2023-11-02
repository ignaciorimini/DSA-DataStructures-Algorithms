#include <stdio.h>
#include <stdlib.h>

// Representation of Int Graph using the Adjacency Matrix.
// Graphviz library is needed to draw the Graphs created int the program.
// Comando para dibujar el grafo: dot -Tpng -o grafo.png grafo.dot

typedef struct _Graph{
    int** matrix;
    int numNodes;
} *Graph;

Graph graph_create(int numNodes){
    Graph graph= malloc(sizeof(struct _Graph));
    graph->numNodes= numNodes;

    // Create the matrix with all the entries in 0.
    graph->matrix= malloc(sizeof(int*)*numNodes);
    for(int i=0; i<numNodes; i++){
        graph->matrix[i]= malloc(sizeof(int)*numNodes);
        for(int j=0; j<numNodes; j++){
            graph->matrix[i][j]= 0;
        }
    }

    return graph;
}

void graph_destroy(Graph graph){
    if(graph == NULL){
        return;
    }

    for(int i=0; i<graph->numNodes; i++){
        free(graph->matrix[i]);
    }

    free(graph->matrix);
    free(graph);
}

void graph_add_edge(Graph graph, int node1, int node2){
    graph->matrix[node1][node2]++;
    graph->matrix[node2][node1]++;
}

int* graph_get_neighbours(Graph graph, int node){
    int* arrayOfNeighbours= malloc(sizeof(int)*graph->numNodes);
    int index= 0;

    if(node >= 0 && node < graph->numNodes){
        for(int i=0; i<graph->numNodes; i++){

            if(graph->matrix[node][i] == 1){
                arrayOfNeighbours[index]= i;
                index++;
            }

        }
    }

    arrayOfNeighbours= realloc(arrayOfNeighbours, sizeof(int)*index);

    return (index == 0) ? NULL : arrayOfNeighbours;
}

int graph_is_null(Graph graph){
    return (graph->numNodes != 0) ? 0 : 1;
}

int graph_is_trivial(Graph graph){
    return (graph->numNodes == 1 && graph->matrix[0][0] == 0) ? 1 : 0;
}

int graph_is_simple(Graph graph){
    for(int i=0; i < graph->numNodes; i++){
        for(int j=i; j < graph->numNodes; j++){
            if(graph->matrix[i][j] == 2){
                return 0;
            }
        }
    }
    return 1;
}

Graph graph_create_complete_graph(int numNodes){
    Graph graph= graph_create(numNodes);
    for(int i=0; i < graph->numNodes; i++){
        for(int j=i+1; j < graph->numNodes; j++){
            graph_add_edge(graph, i, j);
        }
    }

    return graph;
}

Graph graph_create_path_graph(int numNodes){
    Graph graph= graph_create(numNodes);

    if(numNodes==1){
        return graph;
    }else if(numNodes==2){
        graph_add_edge(graph, 0, 1);
    }else{
        for(int i=0; i < graph->numNodes-1; i++){
            graph_add_edge(graph, i, i+1);
        }
    }

    return graph;
}

Graph graph_create_cycle_graph(int numNodes){
    if(numNodes < 3){
        return NULL;
    }

    Graph cycle= graph_create_path_graph(numNodes);
    graph_add_edge(cycle, 0, numNodes-1);
    return cycle;
}

int graph_node_degree(Graph graph, int node){
    if(node > graph->numNodes){
        return -1;
    }

    int degree=0;
    for(int i=0; i<graph->numNodes; i++){
        if(graph->matrix[node][i] > 0){
            degree++;
        }
    }
    return degree;
}

int graph_min_degree(Graph graph){
    int minDegree= graph_node_degree(graph, 0);
    for(int i=1; i < graph->numNodes; i++){
        int newDegree= graph_node_degree(graph, i);
        if(newDegree < minDegree){
            minDegree= newDegree;
        }
    }
    return minDegree;
}

void graph_print_graph(Graph graph, const char* filename){
    printf("Adjacency Matrix:\n");
    for(int i=0; i<graph->numNodes; i++){
        for(int j=0; j<graph->numNodes; j++){
            printf("%d ", graph->matrix[i][j]);
        }
        printf("\n");
    }

    FILE* dotFile = fopen(filename, "w");
    if (dotFile == NULL) {
        perror("Error al abrir el archivo DOT");
        return;
    }

    fprintf(dotFile, "graph G {\n");

    for (int i = 0; i < graph->numNodes; i++) {
        for (int j = i; j < graph->numNodes; j++) {
            int weight = graph->matrix[i][j]; // Peso de la arista (puede ser mayor que 1 para aristas paralelas)

            if (i == j && weight == 2) {
                fprintf(dotFile, "    %d -- %d;\n", i, j); // Arista entre nodos distintos
            }else{

                while (weight > 0) {
                    fprintf(dotFile, "    %d -- %d;\n", i, j); // Arista entre nodos distintos
                    weight--;
                }
            } 
            
        }
    }

    fprintf(dotFile, "}\n");
    fclose(dotFile);
}



int main(){
    Graph graph= graph_create(5);

    graph_add_edge(graph, 1, 1);
    graph_add_edge(graph, 1, 3);
    graph_add_edge(graph, 2, 3);
    graph_add_edge(graph, 2, 3);
    graph_add_edge(graph, 1, 2);

    int* list= graph_get_neighbours(graph, 1);

    graph_print_graph(graph, "graphG.dot");

    printf("The graph is NULL: %d", graph_is_null(graph));
    printf("\n");

    printf("The graph is TRIVIAL: %d", graph_is_trivial(graph));
    printf("\n");

    printf("The graph is SIMPLE: %d", graph_is_simple(graph));
    printf("\n");

    Graph k5= graph_create_complete_graph(5);
    graph_print_graph(k5, "graphk5.dot");

    Graph p3= graph_create_path_graph(3);
    graph_print_graph(p3, "graphp3.dot");

    Graph c3= graph_create_cycle_graph(3);
    graph_print_graph(c3, "graphc3.dot");

    printf("Degree of vertex v0: %d\n", graph_node_degree(k5, 0));
    printf("Min degree of C3: %d\n", graph_min_degree(c3));

    graph_destroy(graph);
    graph_destroy(k5);
    graph_destroy(p3);
    graph_destroy(c3);
    free(list);
    return 0;
}