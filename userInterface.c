#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "userInterface.h"
#include "cities.h"
#include "sort.h"
#include <string.h>
#include "bst.h"

bool isPrefix(char name[], char *str)
{
	int i = 0;
	while (name[i] == str[i])
		i++;
	return (name[i] == '\0');
}


/*int cmp(const void *p1, const void *p2)
{
	return (strCmp(((s_XYCity*)p1)->name, ((s_XYCity*)p2)->name) == true) ? (-1):1;
}*/

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
	s_BST *chosen = NULL;


	const int maxNameSize = 51;
	char c;
	int nbChosen = 0, nbToChoose = 30, nameSize;
	bool goOn = true;
	char name[maxNameSize];
	
	printf("Bonjour, bienvenu dans le TSP ! :D\n");
//	qsort(citiesList, listSize, sizeof(*citiesList), cmp);


	 printf("DEBUG ><\n");
	int i;
	for (i = 0; i < listSize; i++)
		printf("%s\n", citiesList[i].name);
	
	printf("Savez-vous combien de villes vous voulez utiliser [o/n] ? ");
	c = toLower(getchar());

	while (c != 'n' && c != 'o')
	{
		clearInput();
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
			//printf("Youpee, bravo ! :)\n");
			addCities(&chosen, name, citiesList, listSize);
		}
		else if (c == '0' && goOn)
			printf("Enfin fini ! =D\n");
		else
			printf("Mais.... T_T\n");
	}


	return nbChosen;
}



int lowerBound(char name[], s_XYCity *cities, int nbCities)
{
	int begin = 0, end = nbCities, middle;
	while (end - begin > 1)
	{
		middle = (end+begin)/2;
		if (strCmp(name, cities[middle].name))
			end = middle;
		else
			begin = middle;
	}
//	printf("en %d étapes\n", cpt);
	
	return begin;
}


int upperBound(char name[], s_XYCity *cities, int nbCities)
{
	int begin = 0, end = nbCities, middle;
	while (end - begin > 1)
	{
		middle = (end+begin)/2;
		if (isPrefix(name, cities[middle].name))
			begin = middle;
		else
			end = middle;
	}
	
	return begin;
}


void printMatches(char name[], s_XYCity *cities, int nbCities, int *first, int *nbMatches)
{
	char c;
	bool match = true;
	*first = lowerBound(name, cities, nbCities);
//	printf("%s...\n", cities[first].name);
	if (!isPrefix(name, cities[*first].name))
	{
		if (*first < nbCities-1)
		{
			if (isPrefix(name, cities[*first+1].name))
				(*first)++;
			else
				match = false;
		}

		else
			match = false;
	}

	if (match)
	{
		printf("%d\n", *first);
		*nbMatches = upperBound(name, cities+(*first), nbCities-(*first))+1;
		printf("Marche, %d correspondent\n", *nbMatches);
	//printf("Fin : %s\n", cities[first+upperBound(name, cities+first, nbCities-first)].name);
		if (*nbMatches > 50)
		{
			printf("Attention, il y a %d villes correspondant a votre requete ! Voulez-vous toutes les afficher ? ", *nbMatches);
		
			while (c != 'n' && c != 'o')
			{
				clearInput();
				printf("Vous n'avez pas rentre 'o' (oui) ou 'n' (non). Veuillez entrer 'o' ou 'n' : ");
				c = toLower(getchar());
			}
		}

		int i;
		for (i = 0; i < *nbMatches; i++)
			printf("%d : %s\n", i, cities[*first+i].name);

	}
	else
		printf("Aucune ville ne correspond.\n");

}



void addCities(s_BST **root, char name[], s_XYCity *cities, int nbCities)
{
	int firstMatch, nbMatches;
	

	printMatches(name, cities, nbCities, &firstMatch, &nbMatches);
	
	if (nbMatches > 0)
	{
		printf("Veuillez entrer les nombres correspondant aux villes que vous souhaitez ajouter, en espaçant les nombres par une espace, et en terminant par un point.\n");
		int id;
		while (scanf("%d", &id) == 1)
		{
			*root = insert(id+firstMatch, *root);
		}
		clearInput();

		int size = BSTSize(*root);
		int *tab = malloc(size * sizeof(*tab));
		writeInfix(*root, tab);
	
		int i;
		for (i = 0; i < size; i++)
			printf("%s ", cities[tab[i]].name);
		printf("\n\n");
	}
}







