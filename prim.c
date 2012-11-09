#include <stdlib.h>
#include <stdio.h>
#include "prim.h"
#include "edge.h"
#include "heap.h"
#include "error.h"
#include "cities.h"

//The user has chosen nbCities cities, the position of which in the city
//daarrayase is given by citiesList.
s_list *prim(int *citiesList, int nbCities, s_XYCity *citiesDB)
{
	//Useful not to add a vertex twice
	bool *connected = NULL;
	connected = calloc(nbCities, sizeof(*connected));
	int nbConnected = 0;
	//Will contain the length of the minimum edge starting from a vertex in the AVL
	//and pointing to the vettex 'i'
	int *minDists = malloc(nbCities * sizeof(*minDists));
	//To know how much memory allocate to represent the minimal spanning tree
	//as an adjacency list
	int *nbNeighbours = NULL;
	//Edge who originated the addition of a specifig edge
	int *fathers = NULL;
	nbNeighbours = calloc(nbCities, sizeof(*nbNeighbours));
	fathers = malloc(nbCities * sizeof(*fathers));

	//toConnect: vertex not connected yet, otherOne: the other extremity of the edge
	int curCity, minInd;
	int i;

	for (i = 0; i < nbCities; i++)
	{
		fathers[i] = 0;
		minDists[i] = dist(citiesList[i], citiesList[0], citiesDB);
	}

	connected[0] = true;
	nbConnected++;
	//while the tree isn't spanning
	while (nbConnected != nbCities)
	{
		//We take the minimal edge
		for (i = 0; connected[i]; i++);
		minInd = i;
		//We search for the minimal edge
		for (i = minInd+1; i < nbCities; i++)
			if (!connected[i] && minDists[i] < minDists[minInd])
				minInd = i;

		//We've added a new vertex to our spanning tree
		connected[minInd] = true;
		nbConnected++;
		
		nbNeighbours[minInd]++;
		nbNeighbours[fathers[minInd]]++;
		for (curCity = 0; curCity < nbCities; curCity++)
		{
			if (!connected[curCity] && dist(citiesList[curCity], citiesList[minInd], citiesDB) < minDists[curCity])
			{
				minDists[curCity] = dist(citiesList[curCity], citiesList[minInd], citiesDB);
				fathers[curCity] = minInd;
			}
		}
	}
	
	//Those are no longer needed
	free(connected);
	free(minDists);

	return primToTree(fathers, nbNeighbours, nbCities);
}




s_list *primToTree(int *fathers, int *nbNeighbours, int nbCities)
{
	s_list *adjList = NULL;
	adjList = malloc(nbCities * sizeof(*adjList));

	int city, father;

	for (city = 0; city < nbCities; city++)
		adjList[city] = makeList(nbNeighbours[city]);

	//Constructs the adjacency list representation of the non directed graph
	//induced by the spanning tree. We begin at 1 because 0 is the root and
	//so has no father
	for (city = 1; city < nbCities; city++)
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
