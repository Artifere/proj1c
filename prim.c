#include <stdlib.h>
#include "prim.h"
#include "edge.h"
#include "heap.h"
#include "error.h"


//The user has chosen nbCities cities, the position of which in the city
//daarrayase is given by citiesList.
s_list *prim(double **weights, int *citiesList, int nbCities)
{
	s_heap edgeHeap = makeHeap(nbCities*nbCities);

	//Useful not to add a vertex twice
	bool *connected = NULL;
	connected = calloc(nbCities, sizeof(*connected));
	int nbConnected = 0;

	//To know how much memory allocate to represent the minimal spanning tree
	//as an adjacency list
	int *nbNeighbours = NULL;
	//Edge who originated the addition of a specifig edge
	int *fathers = NULL;
	nbNeighbours = calloc(nbCities, sizeof(*nbNeighbours));
	fathers = malloc(nbCities * sizeof(*fathers));

	s_edge mini;
	//toConnect: vertex not connected yet, otherOne: the other extremity of the edge
	int toConnect, otherOne;
	int curCity;

	//To initiate the algorithm: 0 is the first vertex, at a distance of 0
	push((s_edge){0, 0, 0}, &edgeHeap);

	//while the tree isn't spanning
	while (nbConnected != nbCities)
	{
		//We take the minimal edge
		mini = top(edgeHeap);
		pop(&edgeHeap);

		//If it connects two vertices already in the tree, we skip it
		if (!(connected[mini.node1] && connected[mini.node2]))
		{
			//We determine which vertex is the one to be added to the tree
			if (connected[mini.node1])
			{
				toConnect = mini.node2;
				otherOne = mini.node1;
			}
			else
			{
				toConnect = mini.node1;
				otherOne = mini.node2;
			}

			//We add to the heap every edge connecting curCity and another vertex
			//not in the tree.
			for (curCity = 0; curCity < nbCities; curCity++)
				if (!connected[curCity])
					push((s_edge) {weights[citiesList[toConnect]][citiesList[curCity]], curCity, toConnect}, &edgeHeap);

			//We've added curCity to the tree, which is then a little bigger
			nbConnected++;
			connected[toConnect] = true;

			//Fathers serves for remembering which cities are connected in the tree
			fathers[toConnect] = otherOne;
			nbNeighbours[otherOne]++;
			nbNeighbours[toConnect]++;
		}
	}
	
	//Those are no longer needed
	free(connected);
	destroyHeap(&edgeHeap);


	return primToTree(fathers, nbNeighbours, nbCities);
}




s_list *primToTree(int *fathers, int *nbNeighbours, int nbCities)
{
	s_list *adjList = NULL;
	adjList = malloc(nbCities * sizeof(*adjList));

	int city, father;

	for (city = 0; city < nbCities; city++)
		adjList[city] = makeList(nbNeighbours[city]);


	for (city = 0; city < nbCities; city++)
	{
		father = fathers[city];

		pushBack(&adjList[father], city);
		pushBack(&adjList[city], father);
	}

	//These are freed there because the calling function directly returns the
	//result of this function.
	free(fathers);
	free(nbNeighbours);

	return adjList;
}



s_list makeList(int maxSize)
{
	s_list l;
	l.size = 0;
	l.maxSize = maxSize;

	l.data = malloc(maxSize * sizeof(*l.data));

	return l;
}


void pushBack(s_list *l, int elem)
{
	if (l->size >= l->maxSize)
		error("Ajout dans une liste pleine.\n");
	else
	{
		l->data[l->size] = elem;
		l->size++;
	}
}

void destroyList(s_list *l)
{
	free(l->data);
	l->maxSize = 0;
	l->size = 0;
}
