#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<string.h>
#include<assert.h>
#include<time.h>

//Structure for storing edge
struct Edge{
int src,dst,weight;
};

//Structure for storing a graph
struct Graph{
	int vertexNum;
	int edgeNum;
	struct Edge* edges;
};

//Constructs a graph with V vertices and E edges
void createGraph(struct Graph* G,int V,int E){
		G->vertexNum = V;
		G->edgeNum = E;
		G->edges = (struct Edge*) malloc(E * sizeof(struct Edge));		
}

//Adds the given edge to the graph 
void addEdge(struct Graph* G, int src, int dst, int weight){
	static int ind;
	struct Edge newEdge;
	newEdge.src = src;
	newEdge.dst = dst;
	newEdge.weight = weight;
	G->edges[ind++]= newEdge;
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
//to all other vertices using Bellman-Ford.It also detects negative
//weight cycle
void BellmanFord(struct Graph* graph, int src){
	int V = graph->vertexNum;
	int E = graph->edgeNum;
	int dist[V];

	//Initialize distances array as INF for all except source
	//Intialize source as zero
	for(int i=0; i<V; i++)
		dist[i] = INT_MAX;
	dist[src] = 0;

	//Calculate shortest path distance from source to all edges
	//A path can contain maximum (|V|-1) edges
	for(int i=0; i<=V-1; i++)
		for(int j = 0; j<E; j++){
			int u = graph->edges[j].src;
			int v = graph->edges[j].dst;
			int w = graph->edges[j].weight;
			
			if(dist[u]!=INT_MAX && dist[u] + w < dist[v])
				dist[v] = dist[u] + w;
		}
	
	//Iterate inner loop once more to check for negative cycle
	for(int j = 0; j<E; j++){
		int u = graph->edges[j].src;
		int v = graph->edges[j].dst;
		int w = graph->edges[j].weight;
		
		if(dist[u]!=INT_MAX && dist[u] + w < dist[v]){
			printf("Graph contains negative weight cycle. Hence, shortest distance not guaranteed.");
			return;
		}
	}

	print(dist, V);
	
	return;
}



//Driver Function
int main(int argc, char **argv){
	if(argc > 1) {
		srand(time(NULL));
		struct Graph g, g2; 
		int r = rand(), i, j, num=0;
		int S = 10; 
		createGraph(&g, 3, 20);
    	createGraph(&g, S, 20);
		createGraph(&g2, S, 20);
		assert(g.edges != NULL);
    	assert(g.vertexNum == S);
		assert(g.edgeNum == 20);
		for(i=0; i<S; i++) {
			for(j=0; j<S; j++) {
				if(j != i) {
					r = rand() % 100;
					addEdge(&g,i,j,r);
					addEdge(&g2,i,j,r);
					assert(g.edges[num].weight == r);
					assert(g.edges[num].src == i);
					assert(g.edges[num].dst == j);
					num+=2;
				}
			}
		}

		createGraph(&g, 1, 0);
		BellmanFord(&g, 0);

		createGraph(&g, 2, 2);
		addEdge(&g,0,1,10);
		addEdge(&g,1,0,2);
		BellmanFord(&g, 0);
		BellmanFord(&g, 1);

		createGraph(&g, 2, 2);
		addEdge(&g,0,1,10);
		addEdge(&g,0,1,2);
		BellmanFord(&g, 0);

		createGraph(&g, 5, 6);
		addEdge(&g,0,1,10);
		addEdge(&g,0,2,9);
		addEdge(&g,2,1,1);
		addEdge(&g,0,3,4); 
		addEdge(&g,3,4,1);
		addEdge(&g,4,2,3);
		BellmanFord(&g, 0);

		createGraph(&g, 5,7);
		addEdge(&g,0,1,10);
		addEdge(&g,0,2,9);
		addEdge(&g,2,1,1);
		addEdge(&g,0,3,8); 
		addEdge(&g,3,4,1);
		addEdge(&g,0,4,6);
		addEdge(&g,4,2,3);
		BellmanFord(&g, 0);
		S = 4;
		int e = 7;
		int st[7] = {0,0,0,1,1,3,3}; 
		int end[7] = {1,2,3,0,3,2,1};
		int wt[7] = {11,12,13,1,4,18,2};
		createGraph(&g, S, 7);
		for(i=0; i<7;i++)
			addEdge(&g, st[i], end[i], wt[i]);
		BellmanFord(&g, 0);
		BellmanFord(&g, 1);
		BellmanFord(&g, 2);
		BellmanFord(&g, 3);
		return 0;
	}
	int V,E,gsrc;
	int src,dst,weight;
	struct Graph G;
	printf("Enter number of vertices: ");
	scanf("%d",&V);
	printf("Enter number of edges: ");
	scanf("%d",&E);
	createGraph(&G,V,E);
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
	BellmanFord(&G,gsrc);

	return 0;
}


