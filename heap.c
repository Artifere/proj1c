#include <stdlib.h>
#include "edge.h"
#include "heap.h"


s_heap makeHeap(int size)
{
	s_heap h;
	h.size = size+1;
	h.lastInd = 1;

	h.data = NULL;
	h.data = malloc((size+1)*sizeof(*h.data));
	if (h.data == NULL)
		exit(42);
	
	h.data[0] = (s_edge){-1, -1, -1};

	return h;
}

//Realloc memory if...???
//data[0] must be -1, so that we do not go upper


void push(s_edge val, s_heap *heap)
{
	s_edge tmp;
	int ind = heap->lastInd;

	heap->data[heap->lastInd] = val;
	heap->lastInd++;
	heap->size++;
	
	
	while(heap->data[ind].weight < heap->data[ind/2].weight) //Its father
	{
		tmp = heap->data[ind];
		heap->data[ind] = heap->data[ind/2];
		heap->data[ind/2] = tmp;

		ind /=2; //We go up
	}
}


//Check emptyness...
s_edge top(s_heap heap)
{
	if (heap.size > 0)
		return heap.data[1];
	else
	{
		exit(42);
		return heap.data[0];
	}
}



s_edge pop(s_heap *heap)
{
	bool goOn = true;
	s_edge mini = top(*heap);
	s_edge tmp;
	int minInd;
	int ind = 1;

	heap->data[1] = heap->data[heap->lastInd-1];
	heap->lastInd--;
	heap->size--;

	while(goOn) //Its father
	{
		if (ind*2 <heap-> lastInd)
		{
			if (ind*2+1 < heap->lastInd && heap->data[ind*2+1].weight < heap->data[ind*2].weight)
				minInd = ind*2+1;
			else
				minInd = ind*2;

			if (heap->data[ind].weight > heap->data[minInd].weight)
			{
				tmp = heap->data[ind];
				heap->data[ind] = heap->data[minInd];
				heap->data[minInd] = tmp;
			}
			
			ind = minInd;
		}

		else
			goOn = false;
	}

	return mini;
}

