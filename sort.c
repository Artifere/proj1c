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



void qsort(s_XYCity *tab, int size)
{
	if (size < 3)
	{
	}


	int a;
}
