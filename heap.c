#include <stdlib.h>
#include <stdio.h>
#include "edge.h"
#include "heap.h"
#include "error.h"


//Creates a new empty heap. The maximum size of the heap is limited, for it is
//simpler than dynamically reallocate, and it is not needed in the project.
s_heap makeHeap(int maxSize)
{
	s_heap h;
	h.maxSize = maxSize;
	
	//Represents the first empty node of the heap. We don't begin at cell 0 to make
	//the computations of fathers/sons indexes simpler and thus faster.
	h.lastInd = 1;

	h.data = NULL;
	h.data = malloc((maxSize+1)*sizeof(*h.data));
	if (h.data == NULL)
		error("Erreur d'allocation dans l'initialisation du tas.\n");
	
	//Since we only use postive integers (for the third component), it will be
	//as not in the heap. This acts as a "barrier"i.
	h.data[0] = (s_edge){-1, -1, -1};

	return h;
}


//Frees the heap
void destroyHeap(s_heap *h)
{
	free(h->data);

	//Indicates that the heap is no longer valid
	h->maxSize = 0;
	h->lastInd = -1;
	h->data = NULL;
}




//Inserts a new element labeled val.
void push(s_edge val, s_heap *heap)
{
	s_edge tmp = val;
	//We insert it at the first empty node, as a leaf.
	int ind = heap->lastInd;

	heap->data[ind] = val;
	heap->lastInd++;
	
	//We move it up while it is lesser than its father, to preserve the structure of heap.
	//ind/2 is the index of ind's father.
	//The (-1) in the first cell of data is not passable.
	while(heap->data[ind].weight < heap->data[ind/2].weight)
	{
		heap->data[ind] = heap->data[ind/2];
		heap->data[ind/2] = tmp;
		
		ind /=2;
	}
}


//Returns the top of the heap, ie its minimum
s_edge top(s_heap heap)
{
	if (heap.lastInd == 1)
		error("Attention ! Tentative de lecture du minimum d'un tas vide !\n");
	return heap.data[1];
}


//Deletes the minimum of the heap
s_edge pop(s_heap *heap)
{
	bool goOn = true;
	s_edge mini = top(*heap);
	s_edge tmp;
	int minInd;
	int ind = 1;

	//The last element in the heap is now the root
	heap->data[1] = heap->data[heap->lastInd-1];
	heap->lastInd--;

	while(goOn)
	{
		//The node at the index ind has a left son at (2*ind) and a right son at (2*ind+1)
		//We exchange the new root with the least labeled son while the latter has a lesser label.
		if (ind*2 < heap->lastInd)
		{
			//We determine the least labeled of the sons
			if (ind*2+1 < heap->lastInd && heap->data[ind*2+1].weight < heap->data[ind*2].weight)
				minInd = ind*2+1;
			else
				minInd = ind*2;

			//We determine if it is lesser than the new root
			if (heap->data[ind].weight > heap->data[minInd].weight)
			{
				tmp = heap->data[ind];
				heap->data[ind] = heap->data[minInd];
				heap->data[minInd] = tmp;
			}
			
			else
				goOn = false;

			ind = minInd;
		}

		else
			goOn = false;
	}

	return mini;
}

