#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_V 100 // Maximum number of vertices

// Structure to represent an edge
typedef struct Edge {
    int u, v;
} Edge;

// Graph structure
typedef struct Graph {
    int V, E;
    int adj[MAX_V][MAX_V]; // Adjacency matrix
} Graph;

int count = 0, time = 0;
Edge stack[MAX_V * MAX_V];
int top = -1;

void push(int u, int v) {
    stack[++top].u = u;
    stack[top].v = v;
}

void pop() {
    if (top >= 0) {
        printf("%d--%d ", stack[top].u, stack[top].v);
        top--;
    }
}

// Function to create a graph
Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->E = 0;
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            graph->adj[i][j] = 0;
    return graph;
}

// Function to add an edge
void addEdge(Graph* graph, int v, int w) {
    graph->adj[v][w] = 1;
    graph->adj[w][v] = 1;
    graph->E++;
}

void BCCUtil(Graph* graph, int u, int disc[], int low[], int parent[]) {
    disc[u] = low[u] = ++time;
    int children = 0;

    for (int v = 0; v < graph->V; v++) {
        if (graph->adj[u][v]) {
            if (disc[v] == -1) { // If v is not visited
                children++;
                parent[v] = u;
                push(u, v);
                BCCUtil(graph, v, disc, low, parent);

                low[u] = (low[u] < low[v]) ? low[u] : low[v];

                if ((disc[u] == 1 && children > 1) || (disc[u] > 1 && low[v] >= disc[u])) {
                    while (top >= 0 && !(stack[top].u == u && stack[top].v == v)) {
                        pop();
                    }
                    pop();
                    printf("\n");
                    count++;
                }
            }
            else if (v != parent[u] && disc[v] < disc[u]) {
                low[u] = (low[u] < disc[v]) ? low[u] : disc[v];
                push(u, v);
            }
        }
    }
}

void BCC(Graph* graph) {
    int disc[MAX_V], low[MAX_V], parent[MAX_V];
    for (int i = 0; i < graph->V; i++) {
        disc[i] = -1;
        low[i] = -1;
        parent[i] = -1;
    }

    for (int i = 0; i < graph->V; i++) {
        if (disc[i] == -1)
            BCCUtil(graph, i, disc, low, parent);
        
        int j = 0;
        while (top >= 0) {
            j = 1;
            pop();
        }
        if (j) {
            printf("\n");
            count++;
        }
    }
}

int main() {
    Graph* g = createGraph(12);

    //User input to be implemeted
    addEdge(g, 0, 1);
    addEdge(g, 1, 2);
    addEdge(g, 1, 3);
    addEdge(g, 2, 3);
    addEdge(g, 2, 4);
    addEdge(g, 3, 4);
    addEdge(g, 1, 5);
    addEdge(g, 0, 6);
    addEdge(g, 5, 6);
    addEdge(g, 5, 7);
    addEdge(g, 5, 8);
    addEdge(g, 7, 8);
    addEdge(g, 8, 9);
    addEdge(g, 10, 11);

    BCC(g);

    printf("Above are %d biconnected components in graph\n", count);
    free(g);
    return 0;
}