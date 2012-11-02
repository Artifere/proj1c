#include "sort.h"
#include "cities.h"


bool strCmp(char *c1, char *c2)
{
	bool res = true;
	int i = 0;

	while (c1[i] != '\0' && c1[i] == c2[i])
		i++;
	return (c1[i] < c2[i]);
}

void echange(s_XYCity **tab, int i, int j)
{
	s_XYCity stock;
	stock = (*tab)[i];
	(*tab)[i] = (*tab)[j];
	(*tab)[j] = stock ;
}

int median(s_XYCity city1, s_XYCity city2, s_XYCity city3, s_XYCity *pivot)
{
	if(strCmp(city1.name, city2.name))
	{
		if(strCmp(city2.name, city3.name))
		{
			*pivot = city2;
			return 1;
		}
		else
		{
			if(strCmp(city3.name, city1.name))
			{
				*pivot = city1;
				return 0;
			}
			else
			{
				*pivot = city3;
				return 2;
			}
		}
	}
	else
	{
		if(strCmp(city1.name, city3.name)
		{
			*pivot = city1;
			return 0;
		}
		else
		{
			if(strCmp(city2.name, city3.name))
			{	
				*pivot = city3;
				return 2;
			}
			else
			{
				*pivot = city2;
				return 1;
			}
		}
	}
}


int qsort(s_XYCity *tab, int begin, int end)
{
	int i, size, pos;
	size = end-begin+1;
	s_XYCity pivot;
	if (size < 3)
	{
		for (i = begin; i < end; i++)
		{
			if (strCmp(tab[i].name,tab[i+1].name))
				echange(&tab,i,i+1);
		}
		return (begin+1);
	}
	else
	{
		pos = median(tab[begin], tab[begin+1], tab[begin+2], &pivot);
		echange(&tab, begin, begin+pos);
		pos = begin;
		for (i = begin+1; i < end; i++)
		{
			if (strCmp(tab[i].name,pivot.name))
			{
				pos++;
				echange(&tab, pos, i);
			}
		}
		return pos;
	}
}

void qsortbis(s_XYCity *tab, int begin, int end)
{
	if (begin < end)
	{
		int pivot = qsort(tab, begin, end);
		qsortbis(tab, begin, pivot-1);
		qsortbis(tab, pivot+1, end);
	}
}

void sort(s_XYCity *tab, int size)
{
	qsortbis(tab, 0, size-1);
}
		
		
		
