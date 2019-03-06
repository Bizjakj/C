#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<string.h>
#include<time.h>

#include "CuTest.h" 

//Structure for storing a graph
struct Graph{
	int vertexNum;
	int** edges;
};

//Constructs a graph with V vertices and E edges
void createGraph(struct Graph* G,int V){
		G->vertexNum = V;
		G->edges =(int**) malloc(V * sizeof(int*));
		for(int i=0; i<V; i++){
			G->edges[i] = (int*) malloc(V * sizeof(int));
			for(int j=0; j<V; j++)
				G->edges[i][j] = INT_MAX;
			G->edges[i][i] = 0;
		}		
}

//Adds the given edge to the graph 
void addEdge(struct Graph* G, int src, int dst, int weight){
	G->edges[src][dst] = weight;
}


//Utility function to find minimum distance vertex in mdist
int minDistance(int mdist[], int vset[], int V){
	int minVal = INT_MAX, minInd ;
	for(int i=0; i<V;i++)
		if(vset[i] == 0 && mdist[i] < minVal){
		minVal = mdist[i];
		minInd = i;
		}
			
	return minInd;
}

//Utility function to print distances
void print(int dist[], int V){
	printf("\nVertex  Distance\n");
	for(int i = 0; i < V; i++){
		if(dist[i] != INT_MAX)
			printf("%d\t%d\n",i,dist[i]);
		else
			printf("%d\tINF",i);
	}
}

//The main function that finds the shortest path from given source
//to all other vertices using Dijkstra's Algorithm.It doesn't work on negative
//weights
void Dijkstra(struct Graph* graph, int src){
	int V = graph->vertexNum;
	int mdist[V];   //Stores updated distances to vertex
	int vset[V];    // vset[i] is true if the vertex i included
			// in the shortest path tree

	//Initialise mdist and vset. Set distance of source as zero
	for(int i=0; i<V; i++)
		mdist[i] = INT_MAX, vset[i] = 0;
	
	mdist[src] = 0;
	
	//iterate to find shortest path
	for(int count = 0; count<V-1; count++){
		int u = minDistance(mdist,vset,V);
		vset[u] = 1;
		
		for(int v=0; v<V; v++){
			if(!vset[v] && graph->edges[u][v]!=INT_MAX && mdist[u] + graph->edges[u][v] < mdist[v])
				mdist[v] = mdist[u] + graph->edges[u][v];
				
		}
	}

	print(mdist, V);
	
	return;
}

void testCreateGraph(CuTest *tc) {

	int i, j;
	struct Graph g;
	int S = 10; 
    createGraph(&g, S);
    CuAssertIntEquals(tc, S, g.vertexNum);
	for(i=0; i<S; i++) {
		for(j=0; j<S; j++) {
			if(j != i) {
				CuAssertIntEquals(tc, INT_MAX, g.edges[i][j]);
			}
		}
		CuAssertIntEquals(tc, 0, g.edges[i][i]);
	}
}

void testAddEdge(CuTest *tc) {
	srand(time(NULL));
	
	int i, j, r;
	struct Graph g;
	int S = 10; 
    createGraph(&g, S);
	for(i=0; i<S; i++) {
		for(j=0; j<S; j++) {
			if(j != i) {
				r = rand() % 100;
				addEdge(&g,i,j,r);
				CuAssertIntEquals(tc, r, g.edges[i][j]);
			}
		}
	}
}

void testOverideEdge(CuTest *tc) {
	struct Graph g;
	int S = 2; 
	createGraph(&g, S);
	addEdge(&g, 0, 1, 1);
	CuAssertIntEquals(tc, 1, g.edges[0][1]);
	addEdge(&g, 0, 1, 2);
	CuAssertIntEquals(tc, 2, g.edges[0][1]);
}

CuSuite* DijkstraGetSuite() {
        
	CuSuite* suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, testCreateGraph);
	SUITE_ADD_TEST(suite, testAddEdge);
	SUITE_ADD_TEST(suite, testOverideEdge);
    return suite;
}

/*
//Driver Function
int main(int argc, char** argv){
	
	}
	int V,E,gsrc;
	int src,dst,weight;
	struct Graph G;
	printf("Enter number of vertices: ");
	scanf("%d",&V);
	printf("Enter number of edges: ");
	scanf("%d",&E);
	createGraph(&G,V);
	for(int i=0; i<E; i++){
		printf("\nEdge %d \nEnter source: ",i+1);
		scanf("%d",&src);
		printf("Enter destination: ");
		scanf("%d",&dst);
		printf("Enter weight: ");
		scanf("%d",&weight);
		addEdge(&G, src, dst, weight);
	}
	printf("\nEnter source:");
	scanf("%d",&gsrc);
	Dijkstra(&G,gsrc);

	return 0;
}



if(argc > 1) {
		srand(time(NULL));
		struct Graph g, g2; 
		int r = rand(), i, j;
		int S = 10; 
    	createGraph(&g, S);
		createGraph(&g2, S);
    	assert(g.vertexNum == S);
		for(i=0; i<S; i++) {
			for(j=0; j<S; j++) {
				if(j != i) {
					assert(g.edges[i][j] == INT_MAX);
					r = rand() % 100;
					addEdge(&g,i,j,r);
					addEdge(&g2,i,j,r);
					assert(g.edges[i][j] == r);
				}
			}
			assert(g.edges[i][i] == 0);
		}
		addEdge(&g,3,3,5);
		for(i=0; i<S; i++) {
			for(j=0; j<S; j++) {
				if(i != 3 || j != 3) {
					assert(g2.edges[i][j] == g.edges[i][j]);
				} 
			}
		}
		createGraph(&g, 1);
		Dijkstra(&g, 0);

		createGraph(&g, 2);
		addEdge(&g,0,1,2);
		addEdge(&g,0,1,10);
		Dijkstra(&g, 0);

		createGraph(&g, 2);
		Dijkstra(&g, 0);
		Dijkstra(&g, 1);

		createGraph(&g, 2);
		addEdge(&g,0,1,10);
		addEdge(&g,1,0,2);
		Dijkstra(&g, 0);
		Dijkstra(&g, 1);


		createGraph(&g, 5);
		addEdge(&g,0,1,10);
		addEdge(&g,0,2,9);
		addEdge(&g,2,1,1);
		addEdge(&g,0,3,4); 
		addEdge(&g,3,4,1);
		addEdge(&g,4,2,3);
		Dijkstra(&g, 0);

		createGraph(&g, 5);
		addEdge(&g,0,1,10);
		addEdge(&g,0,2,9);
		addEdge(&g,2,1,1);
		addEdge(&g,0,3,8); 
		addEdge(&g,3,4,1);
		addEdge(&g,0,4,6);
		addEdge(&g,4,2,3);
		Dijkstra(&g, 0);
		S = 4;
		int e = 7;
		int start[7] = {0,0,0,1,1,3,3}; 
		int end[7] = {1,2,3,0,3,2,1};
		int weight[7] = {11,12,13,1,4,18,2};
		createGraph(&g, S);
		for(i=0; i<7;i++)
			addEdge(&g, start[i], end[i], weight[i]);
		Dijkstra(&g, 0);
		Dijkstra(&g, 1);
		Dijkstra(&g, 2);
		Dijkstra(&g, 3);
		return 0;
*/