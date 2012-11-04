#include <stdio.h>
#include <stdlib.h>
#include "cities.h"
#include "heap.h"
#include "bst.h"
#include "test.h"
#include "tsp.h"
#include "userInterface.h"
#include "sort.h"


int main(void)
{

//	freopen("error", "w", stdout);
	
	s_XYCity *XYTest = NULL;
	int nbCities = readXYCities("intermediateTownsTest.txt", &XYTest);
	FILE *testWrite = fopen("testXYCities", "w");
	if(testWrite == NULL)
		error("Erreur lors de l'ouverture du fichier test\n");
	if (XYTest == NULL)
		error("AIE AIE AIE, pointeur null ecrit par la fonction readXYCities\n");
	int i, j;


	//Bon, la j'ai mis un test ici... c'est provisoire ! A l'avenir, il sera dans un dossier de test, ou au moins dans un fichier separe !
	for (i = 0; i < nbCities; i++)
	{
		fprintf(testWrite, "%s: %lf; %lf!\n", XYTest[i].name, XYTest[i].x, XYTest[i].y);
	}

	fclose(testWrite);
		

/**	s_BST *root;
	int tabTest[4] = {-7, -50, 42, 84};
	
	root = makeBST(17);
	for (i = 0; i < 4; i++)
	{
		root = insert(tabTest[i], root);
		uglyBSTPrint(root);
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
	*/


	double **weights;
	weights = malloc(nbCities*sizeof(*weights));
	for (i = 0; i < nbCities; i++)
	{
		weights[i] = malloc(nbCities*sizeof(*weights[i]));
		for (j = 0; j < nbCities; j++)
			weights[i][j] = dist(i, j, XYTest);
	}

	int  *tour = malloc(nbCities * sizeof(*tour));
	tsp(weights, nbCities, tour);
	
	
	//To move in test.c
	double length = 0;
	s_list *primRes = prim(weights, 14);
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

	for (i = 0; i < nbCities; i++)
		printf("%s\n", XYTest[tour[i]].name);

	free(tour);
	
	quicksort(XYTest, nbCities);
	printf("\n");
	
	for (i = 0; i < nbCities; i++)
		printf("%s\n", XYTest[i].name);




	int *usersCities = NULL;
	printf("%d\n", getUsersCities(XYTest, nbCities, &usersCities));
	
	free(usersCities);
	usersCities = NULL;
	
		for (i = 0; i < nbCities; i++)
		destroyXYCity(XYTest[i]);
	free(XYTest);

	
	
	
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
	

	
	
	return 0;
}
