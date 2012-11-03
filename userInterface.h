#ifndef USERINTERFACE_H_INCLUDED
#define USERINTERFACE_H_INCLUDED

#include "cities.h"

inline void clearInput(void);
inline char toLower(char c);
int cmp(const void *p1, const void *p2);

bool isPrefix(char name[], char *str);

int getUsersCities(s_XYCity *list, int listSize, int **chosenCities);

void printMatches(char name[], s_XYCity *cities, int nbCities);
int find(char name[], s_XYCity *cities, int nbCities);



#endif
