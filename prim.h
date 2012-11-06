#ifndef PRIM_H_INCLUDED
#define PRIM_H_INCLUDED

struct s_list
{
	int size;
	int *list;
};

typedef struct s_list s_list;

void pushBack(s_list *l, int elem);


s_list *prim(double **weights, int *citiesList, int nbCities);

s_list *primToTree(int *fathers, int *nbSons, int nbCities);





#endif
