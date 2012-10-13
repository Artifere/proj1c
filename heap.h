#ifndef HEAP_H_INCLUDED
#define HEAP_H_INCLUDED
#include "edge.h"

struct s_heap
{
	int lastInd;
	int size;

	s_edge *data;
};

typedef struct s_heap s_heap;


s_heap makeHeap(int size);

void push(s_edge val, s_heap *heap);
s_edge top(s_heap heap);
s_edge pop(s_heap *heap);
















#endif
