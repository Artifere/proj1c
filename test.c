#include <stdio.h>
#include <stdlib.h>
#include "cities.h"
#include "prim.h"
#include "edge.h"
#include "heap.h"





void primTest(void)
{
	const int nbTests = 2;

	FILE *input = NULL, *output = NULL;
	double **weights = NULL;
	char inputName[] = "tests/prim/input/test*.in", outputName[] = "tests/prim/output/test*.out";
	int test, nbNodes;
	int n1, n2;
	s_list *primRes;
	double length;

	for (test = 0; test < nbTests; test++)
	{
		inputName[21] = test + '0';
		outputName[22] = test + '0';

		input = fopen(inputName, "r");
		fscanf(input, "%d\n", &nbNodes);
		
		if ((weights = malloc(nbNodes * sizeof(*weights))) == NULL)
			printf("Erreur d'allocation test Prim\n");
		for (n1 = 0; n1 < nbNodes; n1++)
			if ((weights[n1] = malloc(nbNodes * sizeof(**weights))) == NULL)
				printf("Erreur d'allocation test Prim\n");

		for (n1 = 0; n1 < nbNodes; n1++)
			for (n2 = 0; n2 < nbNodes; n2++)
				fscanf(input, "%lf", &weights[n1][n2]);
		
		primRes = prim(weights, nbNodes);
		length = 0;

		for (n1 = 0; n1 < nbNodes; n1++)
			for (n2 = 0; n2 < primRes[n1].size; n2++)
				length += weights[n1][primRes[n1].list[n2]];
		fclose(input);
	
		for (n1 = 0; n1 < nbNodes; n1++)
		{
			free(primRes[n1].list);
			free(weights[n1]);
		}
		free(primRes);
		free(weights);

		output = fopen(outputName, "w+");
		fprintf(output, "%d\n", (int)length);
		fclose(output);
	}
}
		



void heapTest(void)
{
	const int nbTests = 5;

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

		for (i = 0; i < nbElems; i++)
		{
			fscanf(input, "%lf", &curElem.weight);
			push(curElem, &heap);
		}


		output = fopen(outputName, "w+");
		for (i = 0; i < nbElems; i++)
		{
			curElem = top(heap);
			pop(&heap);

			fprintf(output, "%d ", (int)curElem.weight);
		}
			
		
		fprintf(output, "\n");
		fclose(output);
	}
}


