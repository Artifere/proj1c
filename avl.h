#ifndef Avl_H_INCLUDED
#define Avl_H_INCLUDED

#include <stdbool.h>



inline int max(int a, int b);

struct s_avl
{
	int label;
	int height;
	struct s_avl *ls, *rs;
};
typedef struct s_avl s_avl;


struct s_sadPair
{
	int label;
	s_avl *node;
};
typedef struct s_sadPair s_sadPair;
// No need to provide any methods for this structure: it is intended to be of internal use only

//Useless: just need to insert;
s_avl *makeAvl(int lab);
void destroyAvl(s_avl *toErase);

int getLabel(s_avl *node);
s_avl *getLs(s_avl *father);
s_avl *getRs(s_avl *father);
int getHeight(s_avl *node);


void makeLs(int lab, s_avl *father);
void makeRs(int lab, s_avl *father);


void updateHeight(s_avl *node);
s_avl *insert(int lab, s_avl *node);

s_sadPair seekAndDestroy(s_avl *node);
s_avl *delete(int lab,s_avl  *node);

s_avl *leftRotation(s_avl *node);
s_avl *rightRotation(s_avl *node);
s_avl *leftDoubleRotation(s_avl *node);
s_avl *rightDoubleRotation(s_avl *node);

s_avl *rebalance(s_avl *node);

void uglyAvlPrint(s_avl *node, FILE *writeThere);

int avlSize(s_avl *node);
int *writeInfix(s_avl *node, int *tab);
bool isThisAnAvl(s_avl *node);
bool isThisBalanced(s_avl *node);
void printHeights(s_avl *root);


#endif
