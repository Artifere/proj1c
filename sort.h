#ifndef SORT_H_INCLUDED
#define SOR_H_INCLUDED
#include <stdbool.h>
#include "cities.h"

bool strCmp(char *c1, char *c2);



void swap(s_XYCity **tab, int i, int j);
int median(s_XYCity city1, s_XYCity city2, s_XYCity city3, s_XYCity *pivot);



int qsort(s_XYCity *tab, int begin, int end);


#endif
