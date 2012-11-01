#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED

#include <stdbool.h>



inline int max(int a, int b);

struct s_BST
{
	int label;
	int height;
	struct s_BST *ls, *rs;
};
typedef struct s_BST s_BST;


struct s_sadPair
{
	int label;
	s_BST *node;
};
typedef struct s_sadPair s_sadPair;
// No need to provide any methods for this structure: it is intended to be of internal use only

//Useless: just need to insert;
s_BST *makeBST(int lab);
void destroyBST(s_BST *toErase);

int getLabel(s_BST *node);
s_BST *getLs(s_BST *father);
s_BST *getRs(s_BST *father);
int getHeight(s_BST *node);


void makeLs(int lab, s_BST *father);
void makeRs(int lab, s_BST *father);


void updateHeight(s_BST *node);
s_BST *insert(int lab, s_BST *node);

s_sadPair seekAndDestroy(s_BST *node);
s_BST *delete(int lab, s_BST *node);

s_BST *leftRotation(s_BST *node);
s_BST *rightRotation(s_BST *node);
s_BST *leftDoubleRotation(s_BST *node);
s_BST *rightDoubleRotation(s_BST *node);

s_BST *rebalance(s_BST *node);

void uglyBSTPrint(s_BST *node, FILE *writeThere);

int BSTSize(s_BST *node);
int *writeInfix(s_BST *node, int *tab);
bool isThisABst(s_BST *node);
bool isThisBalanced(s_BST *node);
void printHeights(s_BST *root);


#endif
