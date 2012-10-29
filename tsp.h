#ifndef TSP_H_INCLUDED
#define TSP_H_INCLUDED

#include <stdbool.h>
#include "prim.h"

void read(s_list sons, s_list *tree, int *ind, int *tour, bool *viewed);

int *tsp(double **weights, int nbCities);



#endif
