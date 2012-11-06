#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "tsp.h"
#include "prim.h"
#include "error.h"


//Writes a tour of the graph defined by the adjacency list adj
//The array seen is used not to consider a city twice
//writePos is a pointer to the cell the next city should be written to
int *read(s_list adj, s_list *tree, int *writePos, bool *seen)
{
	int curCity, city;
	//We browse the nodes
	for(city = 0; city < adj.size; city++)
	{
		curCity = adj.data[city];
		if (!seen[curCity])
		{
			seen[curCity] = true;
			*writePos = curCity;
			//We tell the next call that it must write one cell after the one before
			//We also update writePos to be able to write the next node into it
			writePos = read(tree[curCity], tree, writePos+1, seen);
		}
	}

	//For the calling function to update its value of writePos, considering that
	//Some cities have been written down betweenwhiles
	return writePos;
}


//The approximation algorithm for tsp: computes a tour in the graph returned
//by prim
void tsp(double **weights, int *citiesList, int nbCities, int *res)
{
	int city = 0;
	bool *seen = calloc(nbCities, sizeof(*seen));
	s_list *tree = prim(weights, citiesList, nbCities);

// CHECK ==> modify to start with the user's choice !!!!
	res[0] = 9;
	seen[9] = true;
	if (read(tree[9], tree, res+1, seen) - res != nbCities)
		error("Erreur dans la fonction read du tsp pas assez de villes traitees\n");


	//We free the memory for tree (allocated in the prim function) and seen
	for (city = 0; city < nbCities; city++)
		destroyList(&tree[city]);
	free(tree);
	free(seen);
}
