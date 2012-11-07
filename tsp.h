#ifndef TSP_H_INCLUDED
#define TSP_H_INCLUDED

#include <stdbool.h>
#include "prim.h"

int *writeTour(s_list sons, s_list *tree, int *writePos, bool *viewed);

void tsp(int *citiesList, int nbCities, int *res, int startCity, s_XYCity *citiesDB);



#endif
