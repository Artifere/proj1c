#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "userInterface.h"
#include "cities.h"
#include "sort.h"
#include <string.h>


bool isPrefix(char name[], char *str)
{
	int i = 0;
	while (name[i] == str[i])
		i++;
	return (name[i] == '\0');
}


int cmp(const void *p1, const void *p2)
{
	return (strCmp(((s_XYCity*)p1)->name, ((s_XYCity*)p2)->name) == true) ? (-1):1;
}

inline char toLower(char c)
{
	return c|32;
}

inline void clearInput(void)
{
	while (getchar() != '\n');
}


int getUsersCities(s_XYCity *citiesList, int listSize, int **chosenCities)
{
	const int maxNameSize = 51;
	char c;
	int nbChosen = 0, nbToChoose = 30, nameSize;
	bool goOn = true;
	char name[maxNameSize];
	
	printf("Bonjour, bienvenu dans le TSP ! :D\n");
	qsort(citiesList, listSize, sizeof(*citiesList), cmp);


	/* printf("DEBUG ><\n");
	int i;
	for (i = 0; i < citiesListSize; i++)
		printf("%s\n", citiesList[i].name);
	*/
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
	*chosenCities = malloc(nbToChoose * sizeof(**chosenCities));

	printf("Le principe est simple : commencez par entrer les premieres lettres de la ville que vous souhaitez ajouter, puis appuyez sur entree. ");
	printf("Il vous sera alors propose de choisir parmi les villes commencant par les lettres entrees.\n");
	
	clearInput();
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
			while (c != '\n' && nameSize < maxNameSize-1 && goOn)
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
		name[nameSize] = '\0';
		
		if (nameSize == maxNameSize-1 && c != '\n')
		{
			clearInput();
			printf("Veuillez recommencer, vous avez rentre trop de caracteres (plus de 50...).\n");
		}
		else if (c == '\n' && goOn && nameSize > 0)
		{	//blablabla choix de ville toussa toussa
			printf("Youpee, bravo ! :)\n");
			printMatches(name, citiesList, listSize);
		}
		else if (c == '0' && goOn)
			printf("Enfin fini ! =D\n");
		else
			printf("Mais.... T_T\n");
	}


	return nbChosen;
}



int find(char name[], s_XYCity *cities, int nbCities)
{
	int begin = 0, end = nbCities, middle;
	int cpt = 0;
	while (end - begin > 1)
	{
		cpt++;
		middle = (end+begin)/2; //Check if does not create an infinite loop
		if (strCmp(name, cities[middle].name))
			end = middle;
		else
			begin = middle;
	}
	printf("en %d étapes\n", cpt);
	//If end <  nbCities && name is a prefix of cites[end].name
		//==> begin = end
	return begin;
}



void printMatches(char name[], s_XYCity *cities, int nbCities)
{
	int first;
	bool match = true;

	first = find(name, cities, nbCities);
	if (!isPrefix(name, cities[first].name))
	{
		if (first < nbCities-1)
		{
			if (isPrefix(name, cities[first+1].name))
				first++;
			else
				match = false;
		}

		else
			match = false;
	}

	if (match)
		printf("%s\n", cities[first].name);
	else
		printf("Aucune ville ne correspond.\n");







}

