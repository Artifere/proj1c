#include <stdio.h>
#include <stdlib.h>
#include "cities.h"

const int citiesIncrSize = 200;


//Temporary, must be defined in a more general file
void error(char *message)
{
	printf("%s", message);
	exit(42424242);
}


s_cityCoordinates makeCityCoordinates(char *name, int nameSize, double x, double y)
{
	/* Useless actually ==>
		s_cityCoordinates *newElem = malloc(sizeof(*newElem));
	if (newElem == NULL)
		error("Erreur lors de l'allocation d'une ville : il y en a peut-etre trop !\n");
	*/
	s_cityCoordinates newElem;
	newElem.name = malloc(nameSize * sizeof(*newElem.name));

	if(newElem.name == NULL)
		error("Erreur lors de l'allocation pour le nom d'une ville : il y en a peut-etre trop !\n");

	int i;
	for (i = 0; i < nameSize; i++)
			newElem.name[i] = name[i];
	newElem.x = x;
	newElem.y = y;

	return newElem;
}




void readCoordinates(char *filename, s_cityCoordinates* citiesArray) 
{
	FILE *file = fopen(filename, "r");
	int nbLine = 0, posInLine;
	char c;
	//to remove: citiesArray = malloc(incrCitiesSize * sizeof(*citiesArray));
	char read[500];
	double x,y;
	while (c != EOF)
	{
		if (nbLine % citiesIncrSize == 0)
		{
			citiesArray = (s_cityCoordinates*) realloc(citiesArray, (nbLine+citiesIncrSize)*sizeof(*citiesArray));
			
			if (citiesArray == NULL)
				error("Probleme d'allocation du tableau des villes. Il y en a surement trop !\n");
		}

		c = ' ';
		for (posInLine = 0; c != ':'; posInLine++)
		{
			c = (char) fgetc(file);
			read[posInLine] = c;
		}

		posInLine--;
		read[posInLine-1] = '\n'; // for the ':' character
		
		fscanf(file, " %lf; %lf!", &x, &y);

		citiesArray[nbLine] = makeCityCoordinates(read, posInLine, x, y);


		c = (char) fgetc(file); // Soit un retour a la ligne, soit un EOF
		nbLine++;
	}
	citiesArray = (s_cityCoordinates*) realloc(citiesArray, nbLine * sizeof(*citiesArray));
	
	if (citiesArray == NULL)
		error("Erreur au dernier redimensionnement du tableau des villes (pour le reduire a ce qui est utile\
				... Bizarre !\n");
}



