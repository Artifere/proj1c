#ifndef SORT_H_INCLUDED
#define SOR_H_INCLUDED
#include <stdbool.h>
#include "cities.h"


inline char toLower(char c);

bool strCmp(char *c1, char *c2);
void swap(s_XYCity *array, int i, int j);

int median(s_XYCity *array, int ind0, int ind1, int ind2);
int partition(s_XYCity *array, int size);

void quicksort(s_XYCity *array, int size);

#endif
