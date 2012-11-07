#ifndef PRIM_H_INCLUDED
#define PRIM_H_INCLUDED

#include "cities.h"


struct s_list
{
	int maxSize;
	int size;
	int *data;
};

typedef struct s_list s_list;

s_list makeList(int maxSize);
void pushBack(s_list *l, int elem);
void destroyList(s_list *l);

s_list *prim(int *citiesList, int nbCities, s_XYCity *citiesDB);

s_list *primToTree(int *fathers, int *nbSons, int nbCities);





#endif
