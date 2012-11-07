#ifndef USERINTERFACE_H_INCLUDED
#define USERINTERFACE_H_INCLUDED

#include "cities.h"
#include "avl.h"

inline void clearInput(void);
int cmp(const void *p1, const void *p2);

bool isPrefix(char name[], char *str);

s_avl *getUsersCities(s_XYCity *list, int listSize);
void addCities(s_avl **root, char name[], s_XYCity *cities, int nbCities);

int getStartCity(int *usersCities, int nbChosen, s_XYCity *citiesDB);

void printMatches(char name[], s_XYCity *cities, int nbCities, int *first, int *nbMatches);
int lowerBound(char name[], s_XYCity *cities, int nbCities);
int upperBound(char name[], s_XYCity *cities, int nbCities);


void printCities(s_avl *chosen, s_XYCity *citiesDB);

#endif
