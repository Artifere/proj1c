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
	//primTest();
	heapTest();
	avlTest();
	avlRotationsTest();	

	
//	execute();	
	return 0;
}


