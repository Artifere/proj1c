#include <stdio.h>
#include <stdlib.h>
#include "sort.h"
#include "cities.h"


bool strCmp(char *c1, char *c2)
{
	int i = 0;

	while (c1[i] != '\0' && c1[i] == c2[i])
		i++;
	return (c1[i] <= c2[i]);
}

void swap(s_XYCity *tab, int i, int j)
{
	s_XYCity stock;
	stock = tab[i];
	tab[i] = tab[j];
	tab[j] = stock;
}

int median(s_XYCity city1, s_XYCity city2, s_XYCity city3)
{
	//printf("%s %s %s\n", city1.name, city2.name, city3.name);
	int res;
	if(strCmp(city1.name, city2.name))
	{
		if(strCmp(city2.name, city3.name))
			res = 1;
		else
		{
			if(strCmp(city3.name, city1.name))
				res = 0;
			else
				res = 2;
		}
	}
	else
	{
		if(strCmp(city1.name, city3.name))
			res = 0;
		else
		{
			if(strCmp(city2.name, city3.name))
				res = 2;
			else
				res = 1;
		}
	}
	return res;
}


int partition(s_XYCity *tab, int size)
{
	int i, pos;
	s_XYCity pivot;

	pos = median(*tab, *(tab+1), *(tab+2));
	pivot = tab[pos];
	swap(tab, 0, pos);
	pos = 0;

	for (i = 1; i < size; i++)
	{
		if (strCmp(tab[i].name,pivot.name))
		{
			pos++;
			swap(tab, pos, i);
		}
	}

	swap(tab, pos, 0);
	return pos;
}

void quicksort(s_XYCity *tab, int size)
{
	if (size < 3)
	{
		if (size == 2)
			if (strCmp(tab[1].name, tab[0].name))
				swap(tab, 0, 1);
	}

	else
	{
		int posPivot = partition(tab, size);
		printf("deb = %d, fin = %d, pivot = %d\n", 0, size, posPivot);
		quicksort(tab, posPivot);
		quicksort(&tab[posPivot+1], size-posPivot-1);
	}

}
	
		
