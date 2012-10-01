#ifndef H_CITIES_INCLUDED
#define H_CITIES_INCLUDED


#include <stdio.h>

//Example of a structure definition
struct s_cityCoordinates
{
	char *name;
	int x, y;
};
typedef struct s_cityCoordinates s_cityCoordinates;


//TODO: read a file with distances in it... must return a pointer to a city struct array
void readDistances(void);
void readCoordinates(void); //The same, but reads only coordinates
#endif
