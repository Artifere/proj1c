#include <stdio.h>
#include <stdlib.h>
#include "cities.h"
#include "bst.h"

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
	int i;


	//Bon, la j'ai mis un test ici... c'est provisoire ! A l'avenir, il sera dans un dossier de test, ou au moins dans un fichier separe !
	for (i = 0; i < nbCities; i++)
	{
		fprintf(testWrite, "%s: %lf; %lf!\n", XYTest[i].name, XYTest[i].x, XYTest[i].y);
	}

	for (i = 0; i < nbCities; i++)
		destroyXYCity(XYTest[i]);
	free(XYTest);



	s_BST *root;
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
	/*
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
	*/
	return 0;
}
