#ifndef CITIES_H_INCLUDED
#define CITIES_H_INCLUDED




// Example of a structure for storing cities with coordinates
struct s_cityCoordinates
{
	char *name;
	double x, y;
};
typedef struct s_cityCoordinates s_cityCoordinates;

s_cityCoordinates makeCityCoordinates(char *name, int nameSize, double x, double y);


//TODO: read a file with distances in it... must return/take a pointer to a city struct array
void readCoordinates(char *filename, s_cityCoordinates *citiesArray);
void readDistances(void); //The same, but reads only coordinates

#endif
