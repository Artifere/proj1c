#include <stdio.h>
#include <stdlib.h>
#include "cities.h"
#include "heap.h"
#include "avl.h"
#include "test.h"
#include "tsp.h"
#include "userInterface.h"
#include "sort.h"



void execute(void);

int main(void)
{

//	freopen("error", "w", stdout);
	
	//s_XYCity *XYTest = NULL;
//	int nbCities = readXYCities("intermediateTownsTest.txt", &XYTest);
	/*int nbCities = readXYCities("FranceTowns.txt", &XYTest);

	FILE *testWrite = fopen("testXYCities", "w");
	if(testWrite == NULL)
		error("Erreur lors de l'ouverture du fichier test\n");
	if (XYTest == NULL)
		error("AIE AIE AIE, pointeur null ecrit par la fonction readXYCities\n");
	int i, j;
	int *list;
	list = malloc(14 * sizeof(int));
	for (i = 0; i < 14; i++)
	list[i] = i;

	//Bon, la j'ai mis un test ici... c'est provisoire ! A l'avenir, il sera dans un dossier de test, ou au moins dans un fichier separe !
	for (i = 0; i < nbCities; i++)
	{
		fprintf(testWrite, "%s: %lf; %lf!\n", XYTest[i].name, XYTest[i].x, XYTest[i].y);
	}

	fclose(testWrite);
	*/	

/**	s_avl *root;
	int tabTest[4] = {-7, -50, 42, 84};
	
	root = makeAvl(17);
	for (i = 0; i < 4; i++)
	{
		root = insert(tabTest[i], root);
		uglyAvlPrint(root);
		printf("\n");
		printHeights(root);
		printf("\n\n");
	}
	printf("AAAAAAAAAAa");
	
	root = insert(-50, root);
	root = insert(42, root);
	root = insert(-100, root);
	root = insert(17, root);
	root = insert(8, root);
	root = insert(31, root);
	root = insert(84, root);
	
	isThisABst(root);
	printf("\n");
	printHeights(root);


	printf("\n\n");
	//root = delete(17, root); //La racine, hehehe...
	isThisABst(root);
	printf("\n");
	printHeights(root);
	
	printf("%s\n", isThisBalanced(root) ? "Cet arbre est equilibre ! :)" : "Cet arbre n'est pas equilibre. :(");
	
	root = insert(5, root);
	printHeights(root);
	printf("%s\n", isThisBalanced(root) ? "Cet arbre est equilibre ! :)" : "Cet arbre n'est pas equilibre. :(");
	**/

	/**primTest();
	heapTest();
	avlTest();
	avlRotationsTest();	
	**/


	/*double **weights;
	weights = malloc(nbCities*sizeof(*weights));
	for (i = 0; i < nbCities; i++)
	{
		weights[i] = malloc(nbCities*sizeof(*weights[i]));
		for (j = 0; j < nbCities; j++)
			weights[i][j] = dist(i, j, XYTest);
	}

	int  *tour = malloc(nbCities * sizeof(*tour));
	tsp(weights, nbCities, tour);
	
	*/
	//To move in test.c
	/*double length = 0;
	s_list *primRes = prim(weights, list, 14);
	for (i = 0; i < 14; i++)
		for (j = 0; j < primRes[i].size; j++)
			length += weights[i][primRes[i].list[j]];
		
	
	
	printf("Taille : %lf\n", length);
	
	int tab1[13] = {3, 1, 1, 5, 0, 0, 12, 6, 7, 4, 4, 4, 8};
	int tab2[13] = {1, 6, 5, 0, 2, 12, 11, 7, 4, 10, 13, 8, 9};
	
	double bestLength = 0;
	for (i = 0; i < 13; i++)
		bestLength += weights[tab1[i]][tab2[i]];
	printf("Expected : %lf\n", bestLength);
	

	for (i = 0; i < 14; i++)
		free(primRes[i].list);
	free(primRes);
	//End of move

	for (i = 0; i < nbCities; i++)
		free(weights[i]);
	free(weights);


	free(tour);
	
	quicksort(XYTest, nbCities);
	printf("\n");
	



	
	//edgedistances
	/*FILE *file = fopen("testEdgesDistances.txt","r");
	int size;
	fscanf(file,"%d!",&size);
	fclose(file);
	double **adjacency = malloc(size * sizeof(*adjacency));
	for (i =0; i < size; i++)
		adjacency[i] = malloc(size * sizeof(*adjacency[i]));
	readEdgesCities("testEdgesDistances.txt", adjacency);
	for(i = 0; i < size; i++)
	{
		for(j = 0; j < size; j++)
			printf("%d ->%f %d \n",i,adjacency[i][j],j);
	}
	
	for (i = 0; i < size; i++)
		free(adjacency[i]);
	free(adjacency);
	*/
	

	
	execute();	
	return 0;
}



void execute(void)
{	
	int *usersCities = NULL;
	double **weights;
	int i, j;


	s_XYCity *citiesDB = NULL;
	int dbSize = readXYCities("intermediateTownsTest.txt", &citiesDB);
	quicksort(citiesDB, dbSize);

	s_avl *usersCitiesAvl = getUsersCities(citiesDB, dbSize);
	int nbChosen = avlSize(usersCitiesAvl);
	usersCities = malloc (sizeof(*usersCities)*nbChosen);
	writeInfix(usersCitiesAvl, usersCities);
	

	weights = malloc(sizeof(*weights)*dbSize);
	for(i = 0; i < dbSize; i++)
		weights[i] = malloc(sizeof(*weights[i])*dbSize);
	
	for (i= 0; i < nbChosen; i++)
	{
		for (j = 0; j < nbChosen; j++)
			weights[usersCities[i]][usersCities[j]] = dist(usersCities[i], usersCities[j], citiesDB);
	}
	
	int *tour = malloc(sizeof(*tour) * dbSize);
	tsp(weights, usersCities, nbChosen, tour);
	
	for (i = 0; i < nbChosen; i++)
		printf("%s ", citiesDB[tour[i]].name);

	if (nbChosen > 0)
		printf("%s\n", citiesDB[usersCities[tour[0]]].name);
	
	for (i = 0; i < dbSize; i++)
	{
		destroyXYCity(citiesDB[i]);
		free(weights[i]);
	}
	
	free(citiesDB);
	free(usersCities);
	free(weights);
	free(tour);
	destroyAvl(usersCitiesAvl);


	printf("Youhou, j'ai tout fait ! =D\n");
}







