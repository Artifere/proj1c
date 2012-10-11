#include <stdlib.h>
#include <stdio.h>
#include "bst.h"
//temporary: for the error function
#include "cities.h"

inline int max(int a, int b)
{
	return (a < b) ? b:a;
}

s_BST *makeBST(int lab)
{
	s_BST *newNode = malloc(sizeof(*newNode));
	if (newNode == NULL)
		error("Erreur lors de la creation d'un noeud d'un BST\n");

	newNode->ls = NULL;
	newNode->rs = NULL;
	newNode->label = lab;
	newNode->height = 1;
	
	return newNode;
}

void destroyBST(s_BST *node)
{
	if (node != NULL)
	{
		destroyBST(node->ls);
		node->ls = NULL;
		destroyBST(node->rs);
		node-> rs = NULL;
		free(node);
	}
}



int getLabel(s_BST *node)
{
	if (node == NULL)
		error("Tentative de dereferencer un pointeur d'BST NULL (label)\n");

	return node->label;
}

s_BST *getLs(s_BST *father)
{
	if (father == NULL)
		error("Tentative de dereferencer un pointeur d'BST NULL (fils gauche)\n");

	return father->ls;
}

s_BST *getRs(s_BST *father)
{
	if (father == NULL)
		error("Tentative de dereferencer un pointeur d'BST NULL (fils droit)\n");

	return father->rs;
}

int getHeight(s_BST *node)
{
	if (node == NULL)
		return 0;
	else
		return node->height;
}


void makeLs(int lab, s_BST *father)
{
	if (father->ls != NULL)
	{
		error("Attention : on remplace le fils gauche d'un ABR\n"); //Actually more a warning than an error
		destroyBST(father->ls);
	}
	father-> ls = makeBST(lab);
}


void makeRs(int lab, s_BST *father)
{
	if (father->rs != NULL)
	{
		error("Attention : on remplace le fils droit d'un ABR\n"); //Actually more a warning than an error
		destroyBST(father->rs);
	}
	father->rs = makeBST(lab);
}

//Useless?
void changeLs(s_BST *father, s_BST *newLs)
{
	if (father == NULL)
		error("Tentative de changer le fils gauche d'un noeud vide !\n");
	destroyBST(father->ls);
	father->ls = newLs;
}

//Useless?
void changeRs(s_BST *father, s_BST *newLs)
{
	if (father == NULL)
		error("Tentative de changer le fils droit d'un noeud vide !\n");
	destroyBST(father->rs);
	father->rs = newLs;
}

//Useless?
void changeLabel(s_BST *node, int newLab)
{
	if (node == NULL)
		error("Tentative de changer l'etiquette d'un noeud vide !\n");
	node->label = newLab;
}


//Useless?
void changeHeight(s_BST *node, int newHeight)
{
	if (node == NULL)
		error("Tentative de changer la taille d'un noeud vide !\n");
	node->height = newHeight;
}


void updateHeight(s_BST *node)
{
	node->height = max(node->height, 1+getHeight(node->ls));
	node->height = max(node->height, 1+getHeight(node->rs));
}



//Returns the height of the node
void insert(int lab, s_BST *node)
{
	if (node == NULL)
		error("Tentative d'insertion dans un BST vide\n");

	if (lab < node->label)
	{
		if (node->ls == NULL)
			makeLs(lab, node);
		else
			insert(lab, node->ls);
	}

	else if (lab > node->label)
	{
		if (node->rs == NULL)
			makeRs(lab, node);
		else
			insert(lab, node->rs);
	}

	else
		error("Tentative d'ajout dans un BST d'un element redondant\n");
	

	updateHeight(node);

}


s_sadPair seekAndDestroy(s_BST *node)
{
	s_sadPair res;
	if (getRs(node) != NULL)
	{
		res = seekAndDestroy(node->rs);
		node->rs = res.node;
		res.node = node;
	}


	else
	{
		res.node = node->ls;
		res.label = node->label;
	}

	updateHeight(node);

	return res;
}






s_BST *delete(int lab, s_BST *node)
{
	s_BST *newNode = node;
	if (node == NULL)
	{
		error("Tentative de suppression d'un element qui n'est pas dans l'ABR\n");
		newNode = NULL;
	}

	else if (lab == node->label) // It is THE node to suppress
	{
		if (node->ls == NULL)
		{
			newNode = node->rs;

			node->rs = NULL;
			destroyBST(node);
		}

		else if (node->rs == NULL)
		{
			newNode = node->ls;

			node->ls = NULL;
			destroyBST(node);
		}

		else // Apres : choisir dans le fils gauche ou le fils droit selon la taille, etc...
		{
			s_sadPair tmp = seekAndDestroy(node->ls);
			node->ls = tmp.node;
			node->label = tmp.label;
		}
	}


	else
	{
		if (lab < node->label)
			node->ls = delete(lab, node->ls);
	
		else //(lab > getLabel(node))
			node->rs = delete(lab, node->rs);
	}

	updateHeight(node);

		return newNode;
}



//Put a drawing explaining the rotation in comments
s_BST *rightRotation(s_BST *node)
{
	//Check here wether it is justified?


	s_BST *ls = node->ls;
	s_BST *lrgs = node->ls->rs; //Left right grandson; no need to keep a pointer of it

	
	node->ls = lrgs;
	ls->rs = node;
	
	updateHeight(node); //First to be updated: it is a ls's son
	updateHeight(ls);

	return ls;
}


s_BST *leftRotation(s_BST *node)
{
	//Same remarks as for the right rotation
	s_BST *rs = node->rs;
	s_BST *rlgs = node->rs->ls; //Redundant pointer

	node->rs = rlgs;
	rs->ls = node;

	updateHeight(node);
	updateHeight(rs);

	return rs;
}


s_BST *rightDoubleRotation(s_BST *node)
{
	s_BST *ls = node->ls;
	ls = leftRotation(ls);
	node = rightRotation(node);
	return node;
}

s_BST *leftDoubleRotation(s_BST *node)
{
	s_BST *rs = node->rs;
	rs = rightRotation(rs);
	node = leftRotation(node);
	return node;
}

void uglyBSTPrint(s_BST *node)
{
	if (node == NULL)
			printf("V");
	else
	{
		printf("N(%d, ", getLabel(node));
		uglyBSTPrint(getLs(node));
		printf(",");
		uglyBSTPrint(getRs(node));
		printf(")");
	}
}


int *writeInfix(s_BST *node, int *tab)
{
	if (node != NULL)
	{
		tab = writeInfix(getLs(node), tab);
		*tab = getLabel(node);
		//printf("%d ", getLabel(node));
		tab =writeInfix(getRs(node), tab+1);
	}
	return tab;
}

int BSTSize(s_BST *node)
{
	if (node == NULL)
		return 0;
	else
		return 1 + BSTSize(getLs(node)) + BSTSize(getRs(node));
}




//A reecrire, j'ai la flemme de coder un truc propre :s
// Un arbre est un ABR ssi le parcours infixe de ses noeuds donne une liste triee
void isThisABst(s_BST *node)
{
	int size = BSTSize(node);
	
	//Tests to do... NULL...
	int *list = malloc(size * sizeof(*list));
	writeInfix(node, list);
	//printf("==> %d\n", size);
	bool isBST = true;
	int last = list[0];

	int i = 0;
	for (i = 0; i < size; i++)
	{
		printf("%d ", list[i]);
		isBST = isBST && (list[i] >= last);
		last = list[i];
	}
	printf("==>%s", isBST ? "C'est bien un ABR ! =)\n" : "Ce n'est pas un ABR ! =(\n");
}


//Fausse file, prend de la place pour rien, mais simple et efficace
void printHeights(s_BST *root)
{
	printf("Test de la mise a jour des hauteurs :\n");
	int BstSize = BSTSize(root);

	s_BST *queue = malloc(BstSize*sizeof(*queue));
	
	queue[0] = *root;
	int top = 1;
	int bottom = 0;
	s_BST cur;

	while (top != bottom)
	{
		cur = queue[bottom];

		
		printf("%d ", cur.height);

		if (cur.ls != NULL)
		{
			queue[top] = *cur.ls;
			top++;
		}

		if (cur.rs != NULL)
		{
			queue[top] = *cur.rs;
			top++;
		}

		bottom++;
	}
//Bugge, a modifier
//	printf("==>%s\n", goodHeights ? "Les hauteurs sont coherentes." : "Il y a une incoherence dans les hauteurs.");
}	


bool isThisBalanced(s_BST *node)
{
	if (node == NULL)
		return true;
	
	else
		return isThisBalanced(node->ls) && isThisBalanced(node->rs) 
				  && (abs(getHeight(node->ls) - getHeight(node->rs)) <= 1);
}

