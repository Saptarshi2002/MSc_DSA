#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Graph structure
typedef struct {
    int vertices;
    int **adj;
} Graph;

// Create a graph with V vertices
Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->vertices = V;
    graph->adj = (int**)malloc((V + 1) * sizeof(int*));
    for (int i = 0; i <= V; i++) {
        graph->adj[i] = (int*)calloc((V + 1), sizeof(int));
    }
    return graph;
}

// Add edge to graph
void addEdge(Graph* graph, int src, int dest) {
    graph->adj[src][dest] = 1;
}

// Depth First Search function
int dfs(int curr, int dest, Graph* graph, int* visited) {
    if (curr == dest) return 1;
    visited[curr] = 1;
    for (int i = 1; i <= graph->vertices; i++) {
        if (graph->adj[curr][i] && !visited[i]) {
            if (dfs(i, dest, graph, visited)) {
                return 1;
            }
        }
    }
    return 0;
}

// Check if there is a path from src to dest
int isPath(Graph* graph, int src, int dest) {
    int visited[MAX] = {0};
    return dfs(src, dest, graph, visited);
}

// Function to find Strongly Connected Components (SCCs)
void findSCC(Graph* graph) {
    int is_scc[MAX] = {0};
    printf("Strongly Connected Components are:\n");

    for (int i = 1; i <= graph->vertices; i++) {
        if (!is_scc[i]) {
            int scc[MAX], count = 0;
            scc[count++] = i;
            is_scc[i] = 1;

            for (int j = i + 1; j <= graph->vertices; j++) {
                if (!is_scc[j] && isPath(graph, i, j) && isPath(graph, j, i)) {
                    is_scc[j] = 1;
                    scc[count++] = j;
                }
            }
            
            // Print the SCC
            for (int k = 0; k < count; k++) {
                printf("%d ", scc[k]);
            }
            printf("\n");
        }
    }
}

int main() {
    int V = 5;
    Graph* graph = createGraph(V);
    
    int edges[][2] = {
        {1, 3}, {1, 4}, {2, 1}, {3, 2}, {4, 5}
    };
    int numEdges = sizeof(edges) / sizeof(edges[0]);
    
    for (int i = 0; i < numEdges; i++) {
        addEdge(graph, edges[i][0], edges[i][1]);
    }
    
    findSCC(graph);
    

    for (int i = 0; i <= V; i++) {
        free(graph->adj[i]);
    }
    free(graph->adj);
    free(graph);
    
    return 0;
}
