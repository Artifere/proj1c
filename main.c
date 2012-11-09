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
	int choice;
	printf("Bonjour !\n Entrez 0 si vous souhaitez executer les tests, 1 si vous souhaites executer le programme : ");
	while (scanf("%d", &choice) != 1 || (choice != 0 && choice != 1))
	{
		printf("Votre entree n'est pas valide... Entrez 0 pour executer les tests, 1 sinon : ");
	}

	if (choice == 0)
	{
		primTest();
		heapTest();
		avlTest();
		avlRotationsTest();	
		citiesReadingTest();
	}

	else
		execute();	
	return 0;
}


