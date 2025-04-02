#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_NODES 100

// Queue implementation using arrays
int queue[MAX_NODES];
int front = -1, rear = -1;

// Function to check if queue is empty
int isEmpty() {
    return front == -1;
}

// Enqueue an element
void enqueue(int value) {
    if (rear == MAX_NODES - 1) return;
    if (front == -1) front = 0;
    rear++;
    queue[rear] = value;
}

// Dequeue an element
int dequeue() {
    if (isEmpty()) return -1;
    int item = queue[front];
    if (front >= rear) {
        front = -1;
        rear = -1;
    } else {
        front++;
    }
    return item;
}

// BFS function to find the shortest path
void bfs(int graph[MAX_NODES][MAX_NODES], int nodes, int start, int end) {
    int distance[MAX_NODES], parent[MAX_NODES], visited[MAX_NODES] = {0};
    
    for (int i = 0; i < nodes; i++) {
        distance[i] = INT_MAX;
        parent[i] = -1;
    }
    
    enqueue(start);
    visited[start] = 1;
    distance[start] = 0;
    
    while (!isEmpty()) {
        int node = dequeue();
        for (int i = 0; i < nodes; i++) {
            if (graph[node][i] == 1 && !visited[i]) {  // If edge exists and node not visited
                visited[i] = 1;
                distance[i] = distance[node] + 1;
                parent[i] = node;
                enqueue(i);
                if (i == end) break;
            }
        }
    }
    
    // Print shortest distance
    if (distance[end] == INT_MAX) {
        printf("No path exists between %d and %d\n", start, end);
        return;
    }
    printf("Shortest Distance: %d\n", distance[end]);
    
    // Print shortest path
    printf("Shortest Path: ");
    int path[MAX_NODES], path_index = 0;
    for (int v = end; v != -1; v = parent[v]) {
        path[path_index++] = v;
    }
    for (int i = path_index - 1; i >= 0; i--) {
        printf("%d ", path[i]);
    }
    printf("\n");
}

int main() {
    int nodes, edges;
    
    printf("Enter number of nodes: ");
    scanf("%d", &nodes);
    
    printf("Enter number of edges: ");
    scanf("%d", &edges);
    
    int graph[MAX_NODES][MAX_NODES] = {0};
    
    printf("Enter edges (u v):\n");
    for (int i = 0; i < edges; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;
        graph[v][u] = 1; 
    }
    
    int start, end;
    printf("Enter start node: ");
    scanf("%d", &start);
    
    printf("Enter end node: ");
    scanf("%d", &end);
    
    bfs(graph, nodes, start, end);
    
    return 0;
}
