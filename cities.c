#include <stdio.h>
#include <stdlib.h>
#include "cities.h"
#include "error.h"




//Computes the square of the distance between two cities. Since distances are
//only used to be compared with one another, no need to apply sqrt.
double dist(int i, int j, s_XYCity *cities)
{
	double x = cities[i].x - cities[j].x;
	double y = cities[i].y - cities[j].y;
	return x*x+y*y;
}

//Creates a new city (allocates the memory for the name and copies the name).
s_XYCity makeXYCity(char *name, int nameSize, double x, double y)
{
	s_XYCity newElem;
	newElem.name = malloc(nameSize * sizeof(*newElem.name));

	if(newElem.name == NULL)
		error("Erreur lors de l'allocation pour le nom d'une ville : il y en a peut-etre trop !\n");

	//We copy the name of the city into the structure
	int i;
	for (i = 0; i < nameSize; i++)
		newElem.name[i] = name[i];
	newElem.x = x;
	newElem.y = y;

	return newElem;
}


//Frees the name of a city
void destroyXYCity(s_XYCity toErase)
{
	free(toErase.name);
	toErase.name = NULL;
}


int readXYCities(char *filename, s_XYCity **citiesArray) 
{
	//We don't know the number of cities in the file, so we allocate memory
	//step by step
	int citiesIncrSize = 200;
	FILE *file = fopen(filename, "r");
		if(file == NULL)
			error("Fichier de lecture des villes avec coordonnees non ouvert !!!!\n");
	int nbLine = 0, posInLine;
	char c;
	
	char read[500];
	double x,y;
	
	//We read the names/coordinates of the cities
	while ((c = (char) fgetc(file)) != EOF)
	{
		if (nbLine % citiesIncrSize == 0)
		{
			*citiesArray = (s_XYCity*) realloc(*citiesArray, (nbLine+citiesIncrSize)*sizeof(**citiesArray));
			
			if (*citiesArray == NULL)
				error("Probleme d'allocation du arrayleau des villes. Il y en a surement trop !\n");

			citiesIncrSize *= 2;
		}

		//We check that the syntax of the file is correct and we add the
		//terminating character to the name ('\0')
		for (posInLine = 0; c != ':'; posInLine++)
		{
			read[posInLine] = c;
			if((c = (char) fgetc(file)) == EOF)
				error("Fichier de lecture des villes XY mal forme : fin du fichier innatendue\n");
		}
		read[posInLine] = '\0';
		posInLine++;
		
		if (fscanf(file, " %lf; %lf!\n", &x, &y) != 2)
			error("Fscanf n'a pas reussi a lire assez de choses pour les villes XY => fichier mal forme\n");

		//We put the city in the array
		(*citiesArray)[nbLine] = makeXYCity(read, posInLine, x, y);


		nbLine++;
	}

	//If we allocated too much memory, we free the surplus
	*citiesArray = (s_XYCity*) realloc(*citiesArray, nbLine * sizeof(**citiesArray));
	
	if (*citiesArray == NULL)
		error("Erreur au dernier redimensionnement du arrayleau des villes (pour le reduire a ce qui est utile\
				... Bizarre !\n");

	fclose(file);

	return nbLine;
}



