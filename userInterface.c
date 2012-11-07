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
	while (c != '3')
	{
		printf("Entrez le debut d'une nouvelle ville, ou bien 3 si vous avez termine : ");
		nameSize = 0;
		goOn = true;
		c = getchar();
		
		//The user has entered all their cities
		if (c == '3')
			clearInput();
		
		//We ask for some letters, the beginning of a city name
		else
		{
			//We read the input
			while (c != '\n' && nameSize < maxNameSize-1 && goOn)
			{
				//The input is invalid
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
	
		//The input of the user is too long
		if (nameSize == maxNameSize-1 && c != '\n')
		{
			clearInput();
			printf("Veuillez recommencer, vous avez rentre trop de caracteres (plus de 50...).\n");
		}
		else if (c == '\n' && goOn && nameSize > 0)
			addCities(&chosen, name, citiesList, listSize);
		else if (c != '3' || !goOn)
			printf("Votre entree n'est pas valide, veuillez recommencer :\n");
	}


	return chosen;
}


//Use a binary search in the sorted array cities to return the greatest
//element lesser (or equal) than name
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
	
	return begin;
}


//Use a binary search to find the greatest element of which name is prefix
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

//Print the list of the cities of which name is a prefix
void printMatches(char name[], s_XYCity *cities, int nbCities, int *first, int *nbMatches)
{
	char c = '\0';
	bool match = true;
	//If there is one match it is contained in *first if "*first == *name"
	//else it is in *first+1
	*first = lowerBound(name, cities, nbCities);
	
	//We are not in the first case
	if (!isPrefix(name, cities[*first].name))
	{
		//Maybe in the second one
		if (*first < nbCities-1)
		{
			//Whether we are in the second case or not
			if (isPrefix(name, cities[*first+1].name))
				(*first)++;
			else
				match = false;
		}

		//We are in none of the cases
		else
			match = false;
	}


	if (match)
	{
		//We compute the number of cities matching name.
		*nbMatches = upperBound(name, cities+(*first), nbCities-(*first))+1;
		printf("Marche, %d correspondent\n", *nbMatches);
		
		//There are many matches... the user may not want to browse trhough a
		//list of 1000 cities!
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
		
		//We print the cities, assigning a number to each city
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


//Adds some new cities given by the user in the avl.
void addCities(s_avl **root, char name[], s_XYCity *cities, int nbCities)
{
	int firstMatch, nbMatches;
	
	//We print the list of cities
	printMatches(name, cities, nbCities, &firstMatch, &nbMatches);
	
	//If there are no matches, we don't ask the user to choose a city among 0.
	if (nbMatches > 0)
	{
		//errCode is the number of numbers correctly read by scanf, normally 1
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
			}
}



//Prints the current chosen cities. citiesDB is the cities database
void printCities(s_avl *chosen, s_XYCity *citiesDB)
{
	int size = avlSize(chosen);
	int *tab = malloc(size * sizeof(*tab));
	writeInfix(chosen, tab);

	printf("Vous avez choisi les villes suivantes : ");
	int i;
	for (i = 0; i < size; i++)
		printf("%s, ", citiesDB[tab[i]].name);

	putchar('.');
	printf("\n\n");

	free(tab);
}

