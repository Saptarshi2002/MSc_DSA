#include<stdio.h>

void main(){
    int vertices, edges, i, j,u,v;
    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);
    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    int incidenceMatrix[vertices][edges];

    for(i=0;i<vertices;i++)
        for ( j = 0; j < edges; j++)
            incidenceMatrix[i][j]=0;        

    printf("Enter the edges\n");
    for ( i = 0; i < edges; i++)
    {
        scanf("%d%d",&u,&v);
        u--;
        v--;
        incidenceMatrix[u][i]=1;
        incidenceMatrix[v][i]=1;
    }


    for ( i = 0; i < vertices; i++)
    {
        for ( j = 0; j < edges; j++)
        {
            printf("%d",incidenceMatrix[i][j]);
        }
        printf("\n");
        
    }
    
    
}