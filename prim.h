#ifndef PRIM_H_INCLUDED
#define PRIM_H_INCLUDED

struct s_list
{
	int size;
	int *list;
};

typedef struct s_list s_list;


s_list *prim(double **weights, int *citiesList, int nbCities);

s_list *primToTree(int *fathers, int *nbSons, int nbCities);





#endif
