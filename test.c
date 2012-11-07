#include <stdio.h>
#include <stdlib.h>
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


//Executes the tests for Prim's algorithm
void primTest(void)
{
	const int nbTests = 2;

	FILE *input = NULL, *output = NULL;
	double **weights = NULL;

	//The name of the files
	char inputName[] = "tests/prim/input/test*.in", outputName[] = "tests/prim/output/test*.out";
	int test, nbNodes;
	int n1, n2, i;
	s_list *primRes;
	double length;
	int *list;

	//There are several inputs, we test each
	for (test = 0; test < nbTests; test++)
	{
		inputName[21] = test + '0';
		outputName[22] = test + '0';

		input = fopen(inputName, "r");
		fscanf(input, "%d\n", &nbNodes);

		list = malloc(nbNodes * sizeof(*list));
		for (i = 0; i < nbNodes; i++)
			list[i] = i;


		if ((weights = malloc(nbNodes * sizeof(*weights))) == NULL)
			printf("Erreur d'allocation test Prim\n");
		for (n1 = 0; n1 < nbNodes; n1++)
			if ((weights[n1] = malloc(nbNodes * sizeof(**weights))) == NULL)
				printf("Erreur d'allocation test Prim\n");

		//We read the input
		for (n1 = 0; n1 < nbNodes; n1++)
			for (n2 = 0; n2 < nbNodes; n2++)
				fscanf(input, "%lf", &weights[n1][n2]);

		primRes = prim(list, nbNodes, NULL); // CORRECT THIS!!!!
		length = 0;

		//Computes the length of a minimal spanning tree
		for (n1 = 0; n1 < nbNodes; n1++)
			for (n2 = 0; n2 < primRes[n1].size; n2++)
				length += weights[n1][primRes[n1].data[n2]];
		fclose(input);

		for (n1 = 0; n1 < nbNodes; n1++)
		{
			destroyList(&primRes[n1]);
			free(weights[n1]);
		}
		free(primRes);
		free(weights);
		free(list);

		//We write the result
		output = fopen(outputName, "w+");
		fprintf(output, "%d\n", (int)length);
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

