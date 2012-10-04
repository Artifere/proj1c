#ifndef CITIES_H_INCLUDED
#define CITIES_H_INCLUDED

//To be moved elsewhere later
void error(char* message);


// Example of a structure for storing cities with coordinates
struct s_XYCity
{
	char *name;
	double x, y;
};
typedef struct s_XYCity s_XYCity;

s_XYCity makeXYCity(char *name, int nameSize, double x, double y);
void destroyXYCity(s_XYCity toErase);

//TODO: read a file with distances in it... must return/take a pointer to a city struct array
int readXYCities(char *filename, s_XYCity **citiesArray);
int readDistances(void); //The same, but reads only coordinates

#endif
