#include <stdlib.h>
#include "prim.h"
#include <stdbool.h>

void read(s_list sons, s_list *tree, int *ind, int *tour, bool *viewed)
{
        int newCity, son;
        for(son = 0; son < sons.size ; son++)
        {
                        newCity = sons.list[son] ;
                        if (!viewed[newCity])
                        {
                                viewed[newCity] = true ;
                                tour[*ind] = newCity ;
                                *ind = *ind + 1 ;
                                read(tree[sons.list[son]],tree,ind,tour, viewed) ;
                        }
                }
}


int *tsp(double **weights, int nbCities)
{
	int city, town;
	int ind = 0;
	bool *viewed = calloc(nbCities, sizeof(*viewed));
	s_list *tree = prim(weights, nbCities) ;
	bool *marque = NULL ;
	marque = malloc(nbCities) ;
	for (city = 0; city < nbCities; city++)
		marque[city] = false ;
	int *tour = NULL ;
	tour = malloc(nbCities) ;
	town = 0;
	s_list first = tree[town];
	while(first.size == 0)
	{
		town++;
		first = tree[town];
	}
	read(first, tree, &ind, tour, viewed) ;
	return tour ;
}
