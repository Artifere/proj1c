#include <stdio.h>
#include <stdlib.h>
#include "edgeDistances.h"


//Read a file with only distances, no name.
void readEdgesCities(char *filename, double **adjacency)
{
	int edge1, edge2, nbEdges, edge;
	double distance;
	FILE *file = fopen(filename, "r");
	fscanf(file, "%d!\n", &nbEdges);
	for (edge = 0; edge < nbEdges; edge++)
	{
		fscanf(file, "%d %d: %lf!", &edge1, &edge2, &distance);
		edge1--;
		edge2--;

		adjacency[edge1][edge2] = distance;
		adjacency[edge2][edge1] = distance;
	}
	fclose(file);
}
