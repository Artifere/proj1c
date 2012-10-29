#include "tsp.h"
#include <stdlib.h>
#include "prim.h"
#include <stdbool.h>



void read(s_list sons, s_list *tree, int *ind, int *tour, bool *seen)
{
	int newCity, son;
	for(son = 0; son < sons.size ; son++)
	{
		newCity = sons.list[son];
		if (!seen[newCity])
		{
			seen[newCity] = true;
			tour[*ind] = newCity;
			*ind = *ind + 1;
			read(tree[sons.list[son]],tree,ind,tour, seen);
		}
	}
}


int *tsp(double **weights, int nbCities)
{
	int city = 0;
	int ind = 0;
	bool *seen = calloc(nbCities, sizeof(*seen));
	s_list *tree = prim(weights, nbCities);	
	
	int *tour = NULL;
	tour = malloc(nbCities * sizeof(*tour));
	s_list first = tree[city];

	while(first.size == 0)
	{
		city++;
		 first = tree[city];
	}
	read(first, tree, &ind, tour, seen);
	
	 
	 
	for (city = 0; city < nbCities; city++)
		free(tree[city].list);
	free(tree);
	free(seen);
	 
	return tour;
}
