#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "test.h"
#include "cities.h"
#include "prim.h"
#include "edge.h"
#include "heap.h"
#include "avl.h"


//The workings of the tests is the following: we read the inputs in several
//text files, compute a result with the function and write the result into an
//output file. The expected results are in another file, to be compared with
//the output files manhally via a diff.


//Tests the reading of cities
void citiesReadingTest(void)
{
	const int nbTests = 1;
	FILE *output = NULL;

	//The name of the files
	char inputName[] = "tests/reading/input/test*.in", outputName[] = "tests/reading/output/test*.out";
	int test;
	int city;
	s_XYCity *cities;
	int nbCities;
	//There are several inputs, we test each
	for (test = 0; test < nbTests; test++)
	{
		cities = NULL;
		inputName[24] = test + '0';
		outputName[25] = test + '0';
		
		//We read the input
		nbCities = readXYCities(inputName, &cities);

		output = fopen(outputName, "w+");
		for (city = 0; city < nbCities; city++)
		{
			fprintf(output, "%s: %lf.6; %lf.6!\n", cities[city].name, cities[city].x, cities[city].y); 
		}

		for (city = 0; city < nbCities; city++)
			destroyXYCity(cities[city]);


		//We write the result
		fclose(output);
		free(cities);
	}
}




//Executes the tests for Prim's algorithm
void primTest(void)
{
	const int nbTests = 3;

	FILE *output = NULL;

	//The name of the files
	char inputName[] = "tests/prim/input/test*.in", outputName[] = "tests/prim/output/test*.out";
	int test;
	int n1, n2;
	s_list *primRes;
	double length;
	int *list;
	s_XYCity *cities;
	int nbCities;
	//There are several inputs, we test each
	for (test = 0; test < nbTests; test++)
	{
		cities = NULL;
		inputName[21] = test + '0';
		outputName[22] = test + '0';



		//We read the input
		nbCities = readXYCities(inputName, &cities);
		list = malloc(nbCities * sizeof(*list));
		for (n1 = 0; n1 < nbCities; n1++)
			list[n1] = n1;

		primRes = prim(list, nbCities, cities); // CORRECT THIS!!!!
		length = 0;

		//Computes the length of a minimal spanning tree
		for (n1 = 0; n1 < nbCities; n1++)
			for (n2 = 0; n2 < primRes[n1].size; n2++)
				length += sqrt(dist(n1, primRes[n1].data[n2], cities));

		for (n1 = 0; n1 < nbCities; n1++)
		{
			destroyXYCity(cities[n1]);
			destroyList(&primRes[n1]);
		}

		free(cities);
		free(primRes);
		free(list);

		//We write the result
		output = fopen(outputName, "w+");
		fprintf(output, "%lf\n", length);
		fclose(output);
	}
}



//Executes the tests for the heap
void heapTest(void)
{
	const int nbTests = 4;

	FILE *input = NULL, *output = NULL;
	char inputName[] = "tests/heap/input/test*.in", outputName[] = "tests/heap/output/test*.out";
	int test, nbElems, i;
	s_edge curElem = {-1,-1,-1};
	s_heap heap;


	for (test = 0; test < nbTests; test++)
	{
		inputName[21] = test + '0';
		outputName[22] = test + '0';

		input = fopen(inputName, "r");
		fscanf(input, "%d\n", &nbElems);
		heap = makeHeap(nbElems);

		//We read and add the elements to the heap
		for (i = 0; i < nbElems; i++)
		{
			fscanf(input, "%lf", &curElem.weight);
			push(curElem, &heap);
		}

		fclose(input);
		output = fopen(outputName, "w+");
		//We remove the elements... it should give them sorted
		for (i = 0; i < nbElems; i++)
		{
			curElem = top(heap);
			pop(&heap);

			fprintf(output, "%d ", (int)curElem.weight);
		}
		//We reset the heap
		destroyHeap(&heap);

		fprintf(output, "\n");
		fclose(output);
	}
}



//Executes the tests for the avl: check if the tree is "sorted" and balanced.
void avlTest(void)
{
	const int nbTests = 4;

	FILE *input = NULL, *output = NULL;
	char inputName[] = "tests/avl/input/test*.in", outputName[] = "tests/avl/output/test*.out";
	s_avl *root = NULL;
	int test, nbOp, op, elem;
	//opType : Insertion or Deletion
	char opType;

	for (test = 0; test < nbTests; test++)
	{
		inputName[20] = test + '0';
		outputName[21] = test + '0';

		input = fopen(inputName, "r");
		fscanf(input, "%d\n", &nbOp);
		output = fopen(outputName, "w+");

		for (op = 0; op < nbOp; op++)
		{
			fscanf(input, "%c %d\n", &opType, &elem);

			if (opType == 'i')
				root = insert(elem, root);
			else if (opType == 'd')
				root = delete(elem, root);
			else
				fprintf(output, "Fichier de test mal forme.\n");
		}


		fclose(input);

		//We print something if there is an error, else nothing.
		if (!isThisABst(root))
			fprintf(output, "L'arbre n'est pas de recherche.\n");
		if (!isThisBalanced(root))
			fprintf(output, "L'arbre n'est pas equilibré.\n");

		//We reset the avl
		destroyAvl(root);
		root = NULL;
		fclose(output);
	}
}



//"Basics" tests designed only to test the rotations.
void avlRotationsTest(void)
{
	const int nbTests = 5;

	FILE *input = NULL, *output = NULL;
	char inputName[] = "tests/avl rotations/input/test*.in", outputName[] = "tests/avl rotations/output/test*.out";
	s_avl *root = NULL;
	int test, nbOp, op, elem;
	char opType;

	for (test = 0; test < nbTests; test++)
	{
		inputName[30] = test + '0';
		outputName[31] = test + '0';

		input = fopen(inputName, "r");
		fscanf(input, "%d\n", &nbOp);
		output = fopen(outputName, "w+");
		
		for (op = 0; op < nbOp; op++)
		{
			//We read the type of operation and the element
			fscanf(input, "%c %d\n", &opType, &elem);

			if (opType == 'i')
				root = insert(elem, root);
			else if (opType == 'd')
				root = delete(elem, root);
			else
				fprintf(output, "Fichier de test mal forme.\n");
		}

		fclose(input);

		//We print the tree, so as to check whether the rotation has been applied
		uglyAvlPrint(root, output);

		//We free and reset the avl
		destroyAvl(root);
		root = NULL;
		fclose(output);
	}
}

