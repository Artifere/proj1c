#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "userInterface.h"
#include "cities.h"
#include "sort.h"
#include "avl.h"
#include "tsp.h"

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


//Executes everything: asks the user for cities, then computes the result and print it
void execute(void)
{	
	int *usersCities = NULL, *tour;
	int i;
	int startCity;
	int nbChosen, dbSize;
	
	s_avl *usersCitiesAvl;
	s_XYCity *citiesDB = NULL;

	//Reads the cities file and store the results
	dbSize = readXYCities("intermediateTownsTest.txt", &citiesDB);
	//Sorts the cities database to be able to binary search on it
	quicksort(citiesDB, dbSize);

	//Asks the user for cities to be used for the tsp
	usersCitiesAvl = getUsersCities(citiesDB, dbSize);
	nbChosen = avlSize(usersCitiesAvl);

	//Converts the avl into a (sorted) array
	usersCities = malloc (sizeof(*usersCities)*nbChosen);
	writeInfix(usersCitiesAvl, usersCities);
	destroyAvl(usersCitiesAvl);

	//Asks the user the starting city
	startCity = getStartCity(usersCities, nbChosen, citiesDB);
	
	tour = malloc(sizeof(*tour) * (nbChosen+1));
	//We compute the approximation to the tsp problem
	tsp(usersCities, nbChosen, tour, startCity, citiesDB);
	
	//And print the result
	for (i = 0; i <= nbChosen; i++)
		printf("%s ", citiesDB[usersCities[tour[i]]].name);
	

	for (i = 0; i < dbSize; i++)
		destroyXYCity(citiesDB[i]);
	
	free(usersCities);
	free(citiesDB);
	free(tour);
}



//Asks the user for cities and for the starting point of their trip
s_avl *getUsersCities(s_XYCity *citiesDB, int dbSize)
{
	//We put the chosen cities in an avl
	s_avl *chosen = NULL;


	const int maxNameSize = 51;
	char c;
	int nameSize;
	bool goOn = true;
	char name[maxNameSize];
	int choice = -1;
	
	printf("Bonjour, bienvenue dans le TSP ! :D\n");
	printf("Le principe est simple : vous allez avoir le choix entre plusieurs options.");
	printf("Entrez 0 pour inserer une ville, 1 pour en supprimer, 2 pour afficher les ");
	printf("villes deja entrees et 3 si vous avez termine.\n");
	printf("Attention, les caracteres accentues sont interdits !\n\n");
	printf("Quand vous devez entrer une ville, le principe est simple : commencez par entrer les premieres lettres de la ville que vous souhaitez ajouter, puis appuyez sur entree.\n");
	printf("Il vous sera alors propose de choisir parmi les villes commencant par les lettres entrees.\n");


	c = '\n';
	//We ask the user for the cities
	while (choice != 3)
	{

		printf("Entrez votre choix d'option (0 : ajout de ville, 1 : suppression, 2 : affichage et 3 : termine : ");
		//We get the choice of the user
		while (scanf("%d", &choice)!= 1 || (choice != 0 && choice != 1 && choice != 2 && choice != 3))
		{
			clearInput();
			printf("Votre choix n'est pas valide.\n");
			printf("Entrez votre choix d'option (0 : ajout de ville, 1 : suppression, 2 : affichage et 3 : termine) : ");
		}
		clearInput();
		//The user wants to add a city
		if (choice == 0)
		{
			printf("Entrez le debut d'une nouvelle ville : ");
			nameSize = 0;
			goOn = true;
			c = getchar();
		
		
			//We ask for some letters, the beginning of a city name
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

			name[nameSize] = '\0';
	
			//The input of the user is too long
			if (nameSize == maxNameSize-1 && c != '\n')
			{
				clearInput();
				printf("Veuillez recommencer, vous avez rentre trop de caracteres (plus de 50...).\n");
			}
			else if (c == '\n' && goOn && nameSize > 0)
					addCities(&chosen, name, citiesDB, dbSize);

			else if (!goOn)
				printf("Votre entree n'est pas valide, veuillez recommencer :\n");
		}
		
		//The user wants to delete a city
		else if (choice == 1)
		{
			if (chosen == NULL)
				printf("Vous ne pouvez pas retirer de ville : la liste des villes choisies est vide !\n");
			else
				deleteCities(&chosen, citiesDB);
		}

		//The user wants to have the list of the chosen cities printed
		else if (choice == 2)
		{
			if (chosen == NULL)
				printf("Il n'y a aucune ville.\n");
			else
			{
				printf("Vous avez choisi les villes suivantes : ");
				printCities(chosen, citiesDB);
			}
		}
		
		//The user wants to stop adding cities... but the list of chosen ones is empty
		else if (choice == 3 && chosen == NULL)
		{
			printf("La liste des villes choisie est vide... Veuillez ajouter au moins une ville.\n");
			choice = 0;
		}
	}
	return chosen;
}


//Asks the user for a starting point for their trip
int getStartCity(int *usersCities, int nbChosen, s_XYCity *citiesDB)
{
	int i, start;
	printf("Maintenant, nous avons notre liste de villes ! :)\n");
	printf("Vous allez maintenant choisir votre ville de depart.");

	//We print the cities with their indice
	printf("Voici les villes que vous avez choisies :\n");
	for (i = 0; i < nbChosen; i++)
		printf("%d. %s\n", i, citiesDB[usersCities[i]].name);
	printf("Entrez le numero de la ville d'où vous souhaitez partir : ");
	//We scold the user as long as they don't put a valid index
	while (scanf("%d", &start) != 1 || start < 0 || start >= nbChosen)
	{
		clearInput();
		printf("Vous n'avez pas entre un nombre valide. Veuillez entrer un nombre compris ");
		printf("entre 0 et %d : ", nbChosen-1);
	}

	return start;
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
void addCities(s_avl **chosen, char name[], s_XYCity *cities, int nbCities)
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
			if (errCode == 1)
			{
				if (id >= 0 && id < nbMatches)
					*chosen = insert(id+firstMatch, *chosen);
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



//Prints the current chosen cities. citiesDB is the cities daarrayase
void printCities(s_avl *chosen, s_XYCity *citiesDB)
{
	int size = avlSize(chosen);
	int *array = malloc(size * sizeof(*array));
	writeInfix(chosen, array);

	printf("Vous avez choisi les villes suivantes : ");
	int i;
	for (i = 0; i < size-1; i++)
		printf("%s, ", citiesDB[array[i]].name);
	printf("%s", citiesDB[array[size-1]].name);

	putchar('.');
	printf("\n\n");

	free(array);
}



void deleteCities(s_avl **chosen, s_XYCity *cities)
{
	int size = avlSize(*chosen);
	int *array = malloc(size * sizeof(*array));
	int errCode = 1, id;
	writeInfix(*chosen, array);
	
	
	printf("Voici la liste des villes pouvant etre supprimees :\n");
	for (id = 0; id < size; id++)
		printf("%d. %s\n", id, cities[array[id]].name);

	printf("Veuillez entrer les nombres correspondant aux villes que vous souhaitez supprimer, en espaçant les nombres par une espace, et en terminant par un point.\n");
	while (errCode == 1)
	{
		errCode = scanf("%d", &id);
		if (errCode == 1)
		{
			if (id >= 0 && id < size)
				*chosen = delete(array[id], *chosen);
			else
				printf("Attention, %d est invalide : veuillez entrer des nombres entre 0 et %d\n", id, size-1);
		}
		else if (getchar() != '.')
		{
			printf("Attention, vous n'avez pas entre que des nombres positifs. Tout ce que vous avez entre apres le premier caracetere invalide n'a pas ete pris en compte\n");
		}
	}
	clearInput();

	free(array);
}


