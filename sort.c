#include <stdio.h>
#include <stdlib.h>
#include "sort.h"
#include "cities.h"


//Makes c into a non capital letter
inline char toLower(char c)
{
	return c|32;
}

//Returns true if and only if the first string is lesser than the second
//according to the alphabetic order
bool strCmp(char *c1, char *c2)
{
	int i = 0;

	while (c1[i] != '\0' && toLower(c1[i]) == toLower(c2[i]))
		i++;
	return (toLower(c1[i]) <= toLower(c2[i]));
}

//Swaps two elements
void swap(s_XYCity *array, int i, int j)
{
	s_XYCity stock;
	stock = array[i];
	array[i] = array[j];
	array[j] = stock;
}


//Computes the median of three elements. Used by the quicksort algorithm to
//avoid the worst case in O(N²) when the arry is sorted.
int median(s_XYCity *array, int ind0, int ind1, int ind2)
{
	int res;
	if(strCmp(array[ind0].name, array[ind1].name))
	{
		if(strCmp(array[ind1].name, array[ind2].name))
			res = ind1;
		else
		{
			if(strCmp(array[ind2].name, array[ind0].name))
				res = ind0;
			else
				res = ind2;
		}
	}

	else
	{
		if(strCmp(array[ind0].name, array[ind2].name))
			res = 0;
		else
		{
			if(strCmp(array[ind1].name, array[ind2].name))
				res = 2;
			else
				res = 1;
		}
	}
	return res;
}


//Chooses a pivot and split the array in two according to the values of the
//elements compared to the pivot. Returns the index of the pivot.
int partition(s_XYCity *array, int size)
{
	int i, posPivot, nbLesser;
	s_XYCity pivot;

	//We choose the median of the first element, the one in the middle and the last one
	posPivot = median(array, 0, size/2, size-1);
	pivot = array[posPivot];
	//We put the pivot in the first cell
	swap(array, 0, posPivot);
	posPivot = 0;

	nbLesser = 0;
	//We move
	for (i = 1; i < size; i++)
	{
		if (strCmp(array[i].name,pivot.name))
		{
			nbLesser++;
			swap(array, nbLesser, i);
		}
	}

	//We put the pivot at its place
	swap(array, nbLesser, 0);

	return nbLesser;
}

void quicksort(s_XYCity *array, int size)
{
	//If the array is very small, we cannot compute the median, and it does not
	//worth splitting it
	if (size < 3)
	{
		if (size == 2)
			if (strCmp(array[1].name, array[0].name))
				swap(array, 0, 1);
		//Else the array is already sorted
	}

	else
	{
		int posPivot = partition(array, size);

		//We sort recursively
		quicksort(array, posPivot);
		quicksort(&array[posPivot+1], size-posPivot-1);
	}
}


