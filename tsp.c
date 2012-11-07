#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "tsp.h"
#include "prim.h"
#include "error.h"


//Writes a tour of the graph defined by the adjacency list adj
//The array seen is used not to consider a city twice
//writePos is a pointer to the cell the next city should be written to
int *writeTour(s_list adj, s_list *tree, int *writePos, bool *seen)
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
			writePos = writeTour(tree[curCity], tree, writePos+1, seen);
		}
	}

	//For the calling function to update its value of writePos, considering that
	//Some cities have been written down betweenwhiles
	return writePos;
}


//The approximation algorithm for tsp: computes a tour in the graph returned
//by prim. The function returns an array: the list of the cities crossed, in
//the right order.
void tsp(int *citiesList, int nbCities, int *res, int startCity, s_XYCity *citiesDB)
{
	int city = 0;
	bool *seen = calloc(nbCities, sizeof(*seen));
	s_list *tree = prim(citiesList, nbCities, citiesDB);
	
	res[0] = startCity;
	seen[startCity] = true;
	if (writeTour(tree[startCity], tree, res+1, seen) - res != nbCities)
		error("Erreur dans la fonction read du tsp pas assez de villes traitees\n");
	//We terminate at the starting point
	res[nbCities] = startCity;

	//We free the memory for tree (allocated in the prim function) and seen
	for (city = 0; city < nbCities; city++)
		destroyList(&tree[city]);
	free(tree);
	free(seen);
}


//Comutes the length of a tour given by the tsp function
double computeTspLength(int *tour, int nbElems, s_XYCity *citiesDB)
{
	double res = 0;
	int i;
	double x1, x2, y1, y2;

	for (i = 0; i < nbElems-1; i++)
	{
		x1 = citiesDB[tour[i]].x;
		x2 = citiesDB[tour[i+1]].x;
		y1 = citiesDB[tour[i]].y;
		y2 = citiesDB[tour[i+1]].y;

		res += sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
	}


	return res;
}
