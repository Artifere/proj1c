#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "userInterface.h"
#include "cities.h"


inline char toLower(char c)
{
	return c|32;
}




int getUsersCities(s_XYCity *list, int listSize, int *chosenCities)
{
	char c;
	int nbChosen = 0;
	bool goOn = true;

	printf("Bonjour, bienvenu dans le TSP ! :D\n");
	

	printf("Savez-vous combien de villes vous voulez utiliser [o/n] ? ");
	c = toLower(getchar());

	while (c != 'n' && c != 'o')
	{
		printf("Vous n'avez pas rentre 'o' (oui) ou 'n' (non). Veuillez entrer 'o' ou 'n' : ");
		c = toLower(getchar());
	}

	if (c == 'o')
	{	
		while (goOn)
		{
			printf("Combien en voulez-vous ? ");
			if (scanf("%d", &nbChosen) < 0 || nbChosen > listSize)
			{
				printf("Ce n'est pas raisonnable, veuillez entrez un nombre compris entre 0 (apres tout...) et %d (nombre de villes en France : ", listSize);
				while (getchar() != '\n'); // TO change....
			}
			else
				goOn = false;
		}

		chosenCities = malloc(nbChosen * sizeof(*chosenCities));
	}



	return nbChosen;
}

