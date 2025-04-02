#include <stdio.h>
#include <stdlib.h>

#define MAX 100  // Maximum number of vertices

// Disjoint Set Union-Find Data Structure
int parent[MAX], rank[MAX], degree[MAX];

void make_set(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
        degree[i] = 0;
    }
}

int find(int v) {
    if (parent[v] != v)
        parent[v] = find(parent[v]); // Path compression
    return parent[v];
}

void union_sets(int a, int b) {
    a = find(a);
    b = find(b);
    if (a != b) {
        if (rank[a] < rank[b]) {
            parent[a] = b;
        } else if (rank[a] > rank[b]) {
            parent[b] = a;
        } else {
            parent[b] = a;
            rank[a]++;
        }
    }
}

void compute_components(int n, int adjacencyMatrix[MAX][MAX]) {
    make_set(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (adjacencyMatrix[i][j]) {
                union_sets(i, j);
                degree[i]++;
            }
        }
    }
}

void count_components(int n) {
    int component_count = 0;
    int component[MAX] = {0};
    for (int i = 0; i < n; i++) {
        int root = find(i);
        if (!component[root]) {
            component[root] = 1;
            component_count++;
        }
    }
    printf("Number of components: %d\n", component_count);
}

void find_pendant_and_isolated(int n) {
    printf("Pendant vertices: ");
    for (int i = 0; i < n; i++) {
        if (degree[i] == 1)
            printf("%d ", i);
    }
    printf("\n");

    printf("Isolated vertices: ");
    for (int i = 0; i < n; i++) {
        if (degree[i] == 0)
            printf("%d ", i);
    }
    printf("\n");
}

void maximal_cliques(int n, int adjacencyMatrix[MAX][MAX]) {
    printf("Maximal Cliques: \n");
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (adjacencyMatrix[i][j]) {
                for (int k = j + 1; k < n; k++) {
                    if (adjacencyMatrix[i][k] && adjacencyMatrix[j][k]) {
                        printf("{ %d, %d, %d }\n", i, j, k);
                    }
                }
            }
        }
    }
}

int main() {
    int n = 15; // Minimum order 15
    int adjacencyMatrix[MAX][MAX] = {0};
    
    // Example graph input (Modify as needed)
    int edges[][2] = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {5, 6}, {7, 8}, {9, 10}, {10, 11}, {11, 12}, {12, 13}};
    int edgeCount = sizeof(edges) / sizeof(edges[0]);
    
    for (int i = 0; i < edgeCount; i++) {
        int u = edges[i][0], v = edges[i][1];
        adjacencyMatrix[u][v] = adjacencyMatrix[v][u] = 1;
    }

    compute_components(n, adjacencyMatrix);
    count_components(n);
    find_pendant_and_isolated(n);
    maximal_cliques(n, adjacencyMatrix);
    
    return 0;
}


