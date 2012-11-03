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


int partition(s_XYCity *tab, int begin, int end)
{
	int i, size, pos;
	size = end-begin+1;
	s_XYCity pivot;
	/*if (size < 3)
	{
		for (i = begin; i < end; i++)
		{
			if (strCmp(tab[i].name,tab[i+1].name))
				swap(tab,i,i+1);
		}
		return (begin+1);
	}*/
	//else
	//{
		//pos = median(tab[begin], tab[begin+1], tab[begin+2]);
		//pivot = tab[begin+pos];
		pivot = tab[begin];
		//swap(tab, begin, begin+pos);
		pos = begin;
		for (i = begin+1; i < end; i++)
		{
			if (strCmp(tab[i].name,pivot.name))
			{
				pos++;
				swap(tab, pos, i);
			}
		}
		swap(tab, pos, begin);
		return pos;
	//}
}

void quicksort(s_XYCity *tab, int begin, int end)
{
	int i;
	if (begin < end)
	{
		int pivot = partition(tab, begin, end);
		printf("%d\n",pivot);
		for (i = begin; i < end; i++)
			printf("%s\n", tab[i].name);
		printf("\n");
		quicksort(tab, begin, pivot-1);
		quicksort(tab, pivot+1, end);
	}
}

void sort(s_XYCity *tab, int size)
{
	quicksort(tab, 0, size-1);
}
		
		
		
