#include<stdio.h>
#include<stdlib.h>


typedef struct Node {
    int vertex;
    struct Node* next;
}Node;

typedef struct Graph {
    int numvertex;
    struct Node** adjList;
}Graph;



//Create new node
Node* createNode(int vertex){
    Node* new = (Node*)malloc(sizeof(Node*));
    new->vertex = vertex;
    new->next=NULL;

    return new;
}

//Create a Graph
Graph* createGraph(int vertex){
    Graph* new = (Graph*)malloc(sizeof(Graph*));
    new->numvertex = vertex;
    new->adjList=(Node**)malloc(vertex*sizeof(Node*));

    int i;
    for(i=0;i<vertex;i++)
        new->adjList[i]=NULL;

    return new;
}



void addedge(Graph* g,int u,int v){
    Node* node = createNode(v);
    node->next = g->adjList[u];
    g->adjList[u]=node;

    node = createNode(u);
    node->next = g->adjList[v];
    g->adjList[v]=node;
}

void printGraph(Graph* g){
    int i;
    for(i=0;i<g->numvertex;i++){
        Node* temp = g->adjList[i];
        printf("Vertex %d: ",i);
        while(temp){
            printf("%d -> ",temp->vertex);
            temp=temp->next;
        }
        printf("NULL\n");
    }
}

void main(){
    int vertices, edges, i, j,u,v;
    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);
    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    Graph* g = createGraph(vertices);

    printf("Enter the edges\n");
    for ( i = 0; i < edges; i++)
    {
        scanf("%d%d",&u,&v);
        u--;
        v--;
        addedge(g,u,v);
    }


    printGraph(g);
}



