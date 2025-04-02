#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

int adjacencyMatrix[MAX_VERTICES][MAX_VERTICES] = {0};
int visited[MAX_VERTICES] = {0};
int parent[MAX_VERTICES] = {-1};
int numVertices;

void addEdge(int src, int dest) {
    adjacencyMatrix[src][dest] = 1;
    adjacencyMatrix[dest][src] = 1; // Undirected graph
}

void DFS(int vertex) {
    visited[vertex] = 1;
    printf("Visited %d\n", vertex);
    
    for (int i = 0; i < numVertices; i++) {
        if (adjacencyMatrix[vertex][i] == 1 && !visited[i]) {
            parent[i] = vertex; // Record parent in DFS tree
            DFS(i);
        }
    }
}

void printDFSTree() {
    printf("\nDFS Tree Edges:\n");
    for (int i = 0; i < numVertices; i++) {
        if (parent[i] != -1) {
            printf("%d - %d\n", parent[i], i);
        }
    }
}

int main() {
    numVertices = 6;
    
    // Add edges
    addEdge(0, 1);
    addEdge(0, 2);
    addEdge(1, 3);
    addEdge(2, 3);
    addEdge(2, 4);
    addEdge(3, 4);
    addEdge(3, 5);
    addEdge(4, 5);
    
    printf("DFS Traversal:\n");
    DFS(0); 
    
    printDFSTree();
    
    return 0;
}