//from week 9

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "graph.h"

//graph structure
typedef struct GraphRep {
	int nV;
	int nE;
	int **edges;
}GraphRep;

//check if the vertex is valid
int validV(Graph g, Vertex v){
	return(g != NULL && v >= 0 && v < g->nV);
}

//make an edge
Edge mkEdge(Graph g, Vertex v, Vertex w){
	assert(g!= NULL && validV(g,v) && validV(g,w));
	Edge new = {v,w};
	return new;
}
//wth does the above do?
//insert an edge
void insertEdge(Graph g, Vertex v, Vertex w, int wt){
	assert( g!=NULL && validV(g,v) && validV(g,w));
	if(g->edges[v][w] == 0){
		g->edges[v][w] = wt;
		g->nE++;
	}
}
//remove an edge
void removeEdge(Graph g, Vertex v, Vertex w){
	assert( g!=NULL && validV(g,v) && validV(g,w));
	if(g->edges[v][w] != 0){
		g->edges[v][w] = 0;
		g->nE--;
	}
}

Graph newGraph(int nV){
	assert(nV > 0);
	int v, w;
	Graph new = malloc(sizeof(GraphRep));
	assert(new != 0);
	new->nV = nV;
	new->nE = 0;
	new->edges = malloc(nV*sizeof(int *));
	assert(new->edges != 0);
	for ( v= 0; v < nV; v++){
		new->edges[v] = malloc(nV*sizeof(int));
		assert(new->edges[v] != 0);
		for ( w = 0; w < nV; w++){
			new->edges[v][w] = 0;
		}
	}
	return new;
}

void showGraph(Graph g, char **names){
	assert(g != NULL);
	printf("#vertices=%d, #edges=%d\n\n",g->nV,g->nE);
	int v = 0;
	int w = 0;
	while( v < g->nV){
		printf("%d %s\n",v,names[v]);
		while( w < g->nV){
			if(g->edges[v][w]){
				printf("\t%s (%d)\n",names[w],g->edges[v][w]);
			}
			w++;
		}
		printf("\n");
		v++;
	}
}
