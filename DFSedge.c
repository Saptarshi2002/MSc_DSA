#include <stdio.h>
#include <stdlib.h>

// macro and global variables

# define MAX 30

int ds = 0; // dfs start time
int dc = 0; // dfs completion time
int dfsIdx = 0; // dfs array index

// graph structure start

typedef struct Graph{
	int vertices; // total number of vertices
	int visited[MAX]; // visited verices
	int adjM[MAX][MAX]; // adjacency matrix
	int dfsNo[MAX]; // dfs number array
	int dfsCompNo[MAX]; // dfs completion number array
}Graph;

// graph structure end

// graph functions start

void initializeGraph(Graph *g, int v){
	int i, j; // loop
	
	g->vertices = v;
	
	for(i = 0; i < v; i++){
		for(j = 0; j< v; j++){
			g->adjM[i][j] = 0;
		}
		g->visited[i] = 0;
		g->dfsCompNo[i] = 0; 
		g->dfsNo[i] = 0;
	}
}

void addEdge(Graph *g, int src, int dest, int x){
	g->adjM[src][dest] = 1;
	if(x == 2){
		g->adjM[dest][src] = 1;
	}
}

void display(Graph *g){
	int i, j; // loop
	
	for(i = 0; i < g->vertices; i++){
		for(j=0; j< g->vertices; j++){
			printf("%d\t", g->adjM[i][j]);
		}
		printf("\n");
	}
}

void edgeClassification(Graph *g, int v1, int v2){
	
	if(!g->visited[v2]){
		printf("Tree Edge: (%d ---> %d)\n", v1, v2);
	}
	else if(g->dfsNo[v1] > g->dfsNo[v2] && g->dfsCompNo[v2] == 0){
		printf("Back Edge: (%d ---> %d)\n", v1, v2);
	}
	else if(g->dfsNo[v1] < g->dfsNo[v2] && g->dfsCompNo[v2] != 0){
		printf("Forward Edge: (%d ---> %d)\n", v1, v2);
	}
	else if(g->dfsNo[v1] > g->dfsNo[v2] && g->dfsCompNo[v2] != 0){
		printf("Cross Edge: (%d ---> %d)\n", v1, v2);
	}
}

void dfs(Graph *g, int start, int *arr){
	int i;
	
	arr[dfsIdx] = start;
	dfsIdx++;
	g->visited[start] = 1;
	g->dfsNo[start] = ++ds;
	
	for(i = 0; i< g->vertices; i++){
		if(g->adjM[start][i] == 1){
			// edge exists
			
			edgeClassification(g, start, i); // edge classification
			
			if(!g->visited[i]){
				// not visited i
				
				dfs(g, i, arr); // recursive call
			}
		}
	}
	g->dfsCompNo[start] = ++dc;
}

// graph functions end

int main(void){
	Graph g;
	int i, j ; // loop
	int v; // number of vertices;
	int e; // number of edges;
	int start; // start vertex, to start dfs
	int dOrUd; // direct or undirected
	int *dfsResult; // array to store the dfs traversal
	int components = 0; // number of components present in the graph
	int compCheck; // whether want to display component or not
	
	printf("\nEnter number of vertices present in the graph:\t");
	scanf("%d", &v);
	
	printf("\nEnter number of edges present in the graph:\t");
	scanf("%d", &e);
	
	printf("\nEnter \"1\" for directed graph and \"2\" for undirected graph:\t");
	scanf("%d", &dOrUd);
	
	printf("\nEnter start vertex:\t");
	scanf("%d", &start);
	
	initializeGraph(&g, v);
	dfsResult = (int *)calloc(g.vertices, sizeof(int));
	
	for(i=0; i< e; i++){
		int src, dest; // source and destination vertices
		printf("\nEnter source vertex:\t");
		scanf("%d", &src);
		
		printf("\nEnter destination vertex:\t");
		scanf("%d", &dest);
		
		if((src >= 0 && src < g.vertices) && (dest >= 0 && dest < g.vertices)){
			addEdge(&g, src, dest, dOrUd);
		}
		else{
			printf("\nInvalid Input....");
			i--;
			continue;
		}
	}
	
	printf("\nThe adjacency matrix is:\n");
	display(&g);

	dfs(&g, start, dfsResult);
	components++;
	
	for(i = 0; i < g.vertices; i++) {
	    if (!g.visited[i]) {
	        dfs(&g, i, dfsResult);
	        components++;
	    }
	}
	
	printf("\nWant to know the number of components present in this graph? 1 for yes, 2 for no\n");
	scanf("%d", &compCheck);
	if(compCheck == 1){
		printf("\nThe number of components present in the graph is: %d\t", components);
	}
	
	printf("\nThe DFS traversal is:\n");
	for(i = 0 ; i < dfsIdx; i++){
		printf("%d\t", dfsResult[i]);
	}
	
	printf("\nVertex\tDFS Number\tDFS Completion Number\n");
	for(i = 0 ; i < g.vertices; i++){
		printf("%d\t%d\t%10d\n", i, g.dfsNo[i], g.dfsCompNo[i]);
	}
	
	free(dfsResult);
	
	return 0;
}