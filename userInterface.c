#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "userInterface.h"
#include "cities.h"
#include "sort.h"
#include <string.h>
#include "avl.h"


//Returns true if and only if name is prefix of str
bool isPrefix(char name[], char *str)
{
	int i = 0;
	while (toLower(name[i]) == toLower(str[i]) && name[i] != '\0')
		i++;
	return (name[i] == '\0');
}




//Clears the remaining characters entered bu the user and not needed
inline void clearInput(void)
{
	while (getchar() != '\n');
}


//Asks the user for cities and for the starting point of their trip
s_avl *getUsersCities(s_XYCity *citiesList, int listSize, int *startCity)
{
	//We put the chosen cities in an avl
	s_avl *chosen = NULL;


	const int maxNameSize = 51;
	char c;
	int nameSize;
	bool goOn = true;
	char name[maxNameSize];
	
	printf("Bonjour, bienvenue dans le TSP ! :D\n");

	printf("Le principe est simple : commencez par entrer les premieres lettres de la ville que vous souhaitez ajouter, puis appuyez sur entree. ");
	printf("Il vous sera alors propose de choisir parmi les villes commencant par les lettres entrees.\n");


	c = '\0';
	//We ask the user for the cities
	while (c != '0')
	{
		printf("Entrez le debut d'une nouvelle ville, ou bien '0' si vous avez termine : ");
		nameSize = 0;
		goOn = true;
		c = getchar();
		
		//The user has entered all their cities
		if (c == '0')
			clearInput();
		
		//We ask for some letters, the beginning of a city name
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


	return chosen;
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
			begin = middle;//+1 or not... to see
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
	char c = '\0';
	bool match = true;
	*first = lowerBound(name, cities, nbCities);
	printf("%s...%s\n", cities[*first].name, cities[*first+1].name);
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
			c = getchar();	
			while (c != 'n' && c != 'o')
			{
				printf("Vous n'avez pas rentre 'o' (oui) ou 'n' (non). Veuillez entrer 'o' ou 'n' : ");
				c = toLower(getchar());
			}
			clearInput();
		}
		
		if (c != 'n')
		{
			int i;
			for (i = 0; i < *nbMatches; i++)
				printf("%d : %s\n", i, cities[*first+i].name);
		}

		else
			*nbMatches = 0;

	}
	else
	{
		*nbMatches = 0;
		printf("Aucune ville ne correspond.\n");
	}

}



void addCities(s_avl **root, char name[], s_XYCity *cities, int nbCities)
{
	int firstMatch, nbMatches;
	

	printMatches(name, cities, nbCities, &firstMatch, &nbMatches);
	
	if (nbMatches > 0)
	{
		int errCode = 1;
		printf("Veuillez entrer les nombres correspondant aux villes que vous souhaitez ajouter, en espaçant les nombres par une espace, et en terminant par un point.\n");
		int id;
		while (errCode == 1)
		{
			errCode = scanf("%d", &id);
			if (errCode ==1)
			{
				if (id >= 0 && id < nbMatches)
					*root = insert(id+firstMatch, *root);
				else
					printf("Attention, %d est invalide : veuillez entrer des nombres entre 0 et %d\n", id, nbMatches-1);
			}
			else if (getchar() != '.')
			{
				printf("Attention, vous n'avez pas entre que des nombres positifs. Tout ce que vous avez entre apres le premier caracetere invalide n'a pas ete pris en compte\n");
			}
		}
		clearInput();
		int size = avlSize(*root);
		int *tab = malloc(size * sizeof(*tab));
		writeInfix(*root, tab);
	
		int i;
		for (i = 0; i < size; i++)
			printf("%s ", cities[tab[i]].name);
		printf("\n\n");

		free(tab);
	}
}







