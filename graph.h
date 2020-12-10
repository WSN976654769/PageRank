// Graph ADT interface ... COMP2521
#include <stdbool.h>

typedef struct GraphRep *Graph;
typedef struct Node *List;
// vertices are ints
typedef int Vertex;


// edges are pairs of vertices (end-points)
typedef struct Edge {
   Vertex v;
   Vertex w;
} Edge;

Graph newGraph(int);
//void  insertEdge(Graph, Edge);
void  insertEdge(Graph, Edge);
//void  removeEdge(Graph, Edge);
Edge  mkEdge(Graph g, Vertex v, Vertex w);
//Edge  mkEdge(Vertex v, Vertex w);
bool  adjacent(Graph, Vertex, Vertex);
void  showGraph(Graph);
void  freeGraph(Graph);

//void ele_in(Graph);
//List ele_in(Graph g，int order);
List connection(Graph g, int order);
