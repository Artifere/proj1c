#ifndef EDGE_H_INCLUDED
#define EDGE_H_INCLUDED
#include <stdbool.h>
struct s_edge
{
	int weight;
	int node1, node2;
};
typedef struct s_edge s_edge;


bool cmpEdges(s_edge *e1, s_edge *e2);








#endif
