#include <stdio.h>

typedef struct GraphRep *Graph;

typedef int Vertex;
int validV(Graph,Vertex);

typedef struct {Vertex v; Vertex w;} Edge;
void insertEdge(Graph, Vertex, Vertex, int);
void removeEdge(Graph, Vertex, Vertex);

Graph newGraph(int nV);
void showGraph(Graph, char **);
