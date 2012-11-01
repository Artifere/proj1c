#include <stdio.h>
#include <stdlib.h>

void readEdgesCities(char *filename, float ***adjacence)
{
	int sommet1,sommet2,inutile;
	float distance;
	FILE *file = fopen(filename, "r");
	fscanf(file, "%d!",&inutile);
	while (fscanf(file, "%d %d: %f!", &sommet1, &sommet2, &distance) != EOF)
	{
		(*adjacence)[sommet1][sommet2] = distance;
	}
	fclose(file);
}
