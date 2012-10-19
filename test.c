#include <stdio.h>
#include <stdlib.h>
#include "cities.h"
#include "prim.h"
#include "edge.h"
#include "heap.h"


const int nbTests = 2;


void primTest(void)
{
	FILE *input = NULL, *output = NULL;
	double **weights = NULL;
	char inputName[] = "tests/prim/test0.in", outputName[] = "tests/prim/test0.out";
	int i, nbNodes;
	int n1, n2;
	s_list *primRes;
	double length;

	for (i = 0; i < nbTests; i++)
	{
		inputName[15] = i + '0';
		outputName[15] = i + '0';

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
		fprintf(output, "%lf\n", length);
		fclose(output);
	}
}
		

