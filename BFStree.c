#include <stdio.h>
#include <stdbool.h>

#define MAX_NODES 100

int adjMatrix[MAX_NODES][MAX_NODES] = {0};
int numNodes;

// Queue implementation using arrays
int queue[MAX_NODES];
int front = -1, rear = -1;

void enqueue(int value) {
    if (rear == MAX_NODES - 1) {
        printf("Queue is full\n");
    } else {
        if (front == -1) {
            front = 0;
        }
        rear++;
        queue[rear] = value;
    }
}

int dequeue() {
    int item;
    if (front == -1 || front > rear) {
        printf("Queue is empty\n");
        return -1;
    } else {
        item = queue[front];
        front++;
        return item;
    }
}

bool isEmpty() {
    return front == -1 || front > rear;
}

void addEdge(int src, int dest) {
    adjMatrix[src][dest] = 1;
    adjMatrix[dest][src] = 1; // Undirected graph
}

void bfs(int startNode) {
    bool visited[MAX_NODES] = {false};
    int parent[MAX_NODES];
    for (int i = 0; i < numNodes; i++) {
        parent[i] = -1; // -1 means no parent
    }
    
    visited[startNode] = true;
    enqueue(startNode);
    
    printf("BFS Traversal: ");
    
    while (!isEmpty()) {
        int currentNode = dequeue();
        printf("%d ", currentNode);
        
        for (int i = 0; i < numNodes; i++) {
            if (adjMatrix[currentNode][i] == 1 && !visited[i]) {
                visited[i] = true;
                parent[i] = currentNode;
                enqueue(i);
            }
        }
    }
    
    printf("\n\nBFS Tree (Child -> Parent):\n");
    for (int i = 0; i < numNodes; i++) {
        if (parent[i] != -1) {
            printf("%d -> %d\n", i, parent[i]);
        } else if (i != startNode) {
            printf("%d -> (Not reachable)\n", i);
        }
    }
}

int main() {
    printf("Enter number of nodes in the graph: ");
    scanf("%d", &numNodes);
    
    int numEdges;
    printf("Enter number of edges: ");
    scanf("%d", &numEdges);
    
    printf("Enter edges (source destination):\n");
    for (int i = 0; i < numEdges; i++) {
        int src, dest;
        scanf("%d %d", &src, &dest);
        addEdge(src, dest);
    }
    
    int startNode;
    printf("Enter starting node for BFS: ");
    scanf("%d", &startNode);
    
    bfs(startNode);
    
    return 0;
}