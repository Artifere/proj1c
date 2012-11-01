#include "tsp.h"
#include <stdlib.h>
#include <stdio.h>
#include "prim.h"
#include <stdbool.h>



int *read(s_list sons, s_list *tree, int *writePos, bool *seen)
{
	int curSon, son;
	for(son = 0; son < sons.size ; son++)
	{
		curSon = sons.list[son];
		if (!seen[curSon])
		{
			seen[curSon] = true;
			*writePos = curSon;
			writePos = read(tree[curSon], tree, writePos+1, seen);
		}
	}

	return writePos;
}


void tsp(double **weights, int nbCities, int *res)
{
	int city = 0;
	bool *seen = calloc(nbCities, sizeof(*seen));
	s_list *tree = prim(weights, nbCities);

	s_list first = tree[city];

	//To examine: must be possible to pass as an argument the id of a city which has some sons
	while(first.size == 0)
	{
		city++;
		first = tree[city];
	}
	if (read(first, tree, res, seen) - res != nbCities)
		printf("Erreur dans la fonction read du tsp pas assez de villes traitees\n");



	for (city = 0; city < nbCities; city++)
		free(tree[city].list);
	free(tree);
	free(seen);
}
