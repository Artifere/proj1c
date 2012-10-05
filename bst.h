#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED


struct s_BST
{
	int label;
	struct s_BST *ls, *rs;
};
typedef struct s_BST s_BST;


s_BST *makeBST(int lab);
void destroyBST(s_BST *toErase);

int getLabel(s_BST *node);
s_BST *getLs(s_BST *father);
s_BST *getRs(s_BST *father);


void makeLs(int lab, s_BST *father);
void makeRs(int lab, s_BST *father);

void insert(int lab, s_BST *node);





#endif
