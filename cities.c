#include <stdio.h>
#include <stdlib.h>
#include "cities.h"


//Maybe it should evolve as we discover the file is a big one, not to have to many reallocations, so it would not be a constant, nor a global variable
const int citiesIncrSize = 200;


//Temporary, must be defined in a more general file
void error(char *message)
{
	printf("%s", message);
	//exit(42424242);
}


double dist(int i, int j, s_XYCity *cities)
{
	double x = cities[i].x - cities[j].x;
	double y = cities[i].y - cities[j].y;
	return x*x+y*y;
}


s_XYCity makeXYCity(char *name, int nameSize, double x, double y)
{
	/* Useless actually ==>
		s_XYCity *newElem = malloc(sizeof(*newElem));
	if (newElem == NULL)
		error("Erreur lors de l'allocation d'une ville : il y en a peut-etre trop !\n");
	*/
	s_XYCity newElem;
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


void destroyXYCity(s_XYCity toErase)
{
	free(toErase.name);
	toErase.name = NULL; // Par precaution
	//free(toErase) ?!?! ==> si on a alloue un tableau, on n'en a pas besoin... ou alors on libere chaque element un par un...
}




int readXYCities(char *filename, s_XYCity **citiesArray) 
{
	FILE *file = fopen(filename, "r");
		if(file == NULL)
			error("Fichier de lecture des villes avec coordonnees non ouvert !!!!\n");
	int nbLine = 0, posInLine;
	char c;
	//to remove: citiesArray = malloc(incrCitiesSize * sizeof(*citiesArray));
	char read[500];
	double x,y;
	
	while ((c = (char) fgetc(file)) != EOF)
	{
		if (nbLine % citiesIncrSize == 0)
		{
			*citiesArray = (s_XYCity*) realloc(*citiesArray, (nbLine+citiesIncrSize)*sizeof(**citiesArray));
			
			if (*citiesArray == NULL)
				error("Probleme d'allocation du tableau des villes. Il y en a surement trop !\n");
		}

		for (posInLine = 0; c != ':'; posInLine++)
		{
			read[posInLine] = c;
			if((c = (char) fgetc(file)) == EOF)
				error("Fichier de lecture des villes XY mal forme : fin du fichier innatendue\n");
		}

		//Not needed anymore I think ==>read[posInLine-1] = '\0'; // replace the ':' character
		
		if (fscanf(file, " %lf; %lf!\n", &x, &y) != 2)
			error("Fscanf n'a pas reussi a lire assez de choses pour les villes XY => fichier mal forme\n");

		(*citiesArray)[nbLine] = makeXYCity(read, posInLine, x, y);


		//Not needed anymore I think ==>c = (char) fgetc(file); // Soit un retour a la ligne, soit un EOF
		nbLine++;
	}
	*citiesArray = (s_XYCity*) realloc(*citiesArray, nbLine * sizeof(**citiesArray));
	
	if (*citiesArray == NULL)
		error("Erreur au dernier redimensionnement du tableau des villes (pour le reduire a ce qui est utile\
				... Bizarre !\n");

	fclose(file);

	return nbLine;
}



