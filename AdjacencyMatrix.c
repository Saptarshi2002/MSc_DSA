#include<stdio.h>

void main(){
    int vertices, edges, i, j,u,v;
    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);
    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    int adjacencyMatrix[vertices][vertices];

    for(i=0;i<vertices;i++)
        for ( j = 0; j < vertices; j++)
            adjacencyMatrix[i][j]=0;        

    printf("Enter the edges\n");
    for ( i = 0; i < edges; i++)
    {
        scanf("%d%d",&u,&v);
        u--;
        v--;
        adjacencyMatrix[u][v]=1;
        adjacencyMatrix[v][u]=1;
    }


    for ( i = 0; i < vertices; i++)
    {
        for ( j = 0; j < vertices; j++)
        {
            printf("%d",adjacencyMatrix[i][j]);
        }
        printf("\n");
        
    }
    
    
}