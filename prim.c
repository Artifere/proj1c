#include <stdlib.h>
#include "prim.h"
#include "edge.h"
#include "heap.h"



s_list *prim(int **weights, int nbCities)
{
	s_heap edgeHeap;
	//edgeHeap = malloc((1+nbCities*nbCities) * sizeof(*edgesHeap));
	
	bool *connected = NULL;
	connected = calloc(nbCities, sizeof(*connected));
	int nbConnected = 0;

	int *nbSons = NULL;
	int *fathers = NULL;
	fathers = calloc(nbCities, sizeof(*nbSons));


	s_edge mini;
	int toConnect, otherOne;
	int curCity;	
	
	
	push((s_edge){0, 0, 0}, &edgeHeap);
	while (nbConnected != nbCities)
	{
		mini = top(edgeHeap);
		pop(&edgeHeap);

		if (!(connected[mini.node1] && connected[mini.node2]))
		{
			if (connected[mini.node1])
			{
				toConnect = mini.node1;
				otherOne = mini.node2;
			}
			else
			{
				toConnect = mini.node2;
				otherOne = mini.node1;
			}

			for (curCity = 0; curCity < toConnect; curCity++)
				if (!connected[curCity])
					push((s_edge) {weights[toConnect][curCity], curCity, toConnect}, &edgeHeap);
			for (curCity = toConnect+1; curCity < nbCities; curCity++)
				if (!connected[curCity])
					push((s_edge){weights[toConnect][curCity], toConnect, curCity}, &edgeHeap);
			

			nbConnected++;
			connected[toConnect] = true;

			fathers[toConnect] = otherOne;
			nbSons[otherOne]++;
		}
	}
	
	return primToTree(fathers, nbSons, nbCities);
}




s_list *primToTree(int *fathers, int *nbSons, int nbCities)
{
	s_list *sonsList = NULL;
	sonsList = malloc(nbCities * sizeof(*sonsList));

	int city, father;

	for (city = 0; city < nbCities; city++)
	{
		sonsList[city].list = malloc(nbSons[city]*sizeof(*sonsList[city].list));
		sonsList[city].size = 0;
	}

	for (city = 0; city < nbCities; city++)
	{
		father = fathers[city];
		sonsList[father].list[sonsList[father].size] = city;
		sonsList[father].size++;
	}


	return sonsList;
}
