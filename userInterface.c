#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "userInterface.h"
#include "cities.h"

inline char toLower(char c);
inline char toLower(char c)
{
	return c|32;
}

inline void clearInput(void)
{
	while (getchar() != '\n');
}


int getUsersCities(s_XYCity *list, int listSize, int *chosenCities)
{
	const int maxNameSize = 100;
	char c;
	int nbChosen = 0, nbToChoose = 30, nameSize;
	bool goOn = true;
	char name[maxNameSize];
	
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
			if (scanf("%d", &nbToChoose) < 0 || nbToChoose > listSize)
			{
				printf("Ce n'est pas raisonnable, veuillez entrez un nombre compris entre 0 (apres tout...) et %d (nombre de villes en France : ", listSize);
				clearInput();	
			}
			else
				goOn = false;
		}	
	}
	chosenCities = malloc(nbToChoose * sizeof(*chosenCities));

	printf("Le principe est simple : commencez par entrer les premieres lettres de la ville que vous souhaitez ajouter, puis appuyez sur entree. \
			  Il vous sera alors propose de choisir parmi les villes commencant par les lettres entrees.\n");
	
	getchar();
	while (c != '0')
	{
		printf("Entrez le debut d'une nouvelle ville, ou bien '0' si vous avez termine : ");
		nameSize = 0;
		goOn = true;
		c = getchar();
		if (c == '0')
			clearInput();
		else
		{
			while (c != '\n' && nameSize < maxNameSize && goOn)
			{
				printf("%c", c);
				if ((c < 'A' || c > 'z' || (c > 'Z' && c < 'a')) && c != '-' && c != '\'' && c != ' ' && c != '\n')
				{
					printf("erreur : %c\n", c);
					clearInput();
					goOn = false;
				}
			
				else
				{
					name[nameSize] = c;
					nameSize++;
					c = getchar();
				}
			}
		}
		
		if (c == '\n' && goOn && nameSize > 0)
			//blablabla choix de ville toussa toussa
			printf("Youpee, bravo ! :)\n");
		else if (c == '0' && goOn)
			printf("Enfin fini ! =D\n");
		else
			printf("Mais.... T_T\n");
	}


	



	return nbChosen;
}

