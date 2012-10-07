#include <stdlib.h>
#include <stdio.h>
#include "bst.h"
//temporary: for the error function
#include "cities.h"

s_BST *makeBST(int lab)
{
	s_BST *newNode = malloc(sizeof(*newNode));
	if (newNode == NULL)
		error("Erreur lors de la creation d'un noeud d'un BST\n");

	newNode->ls = NULL;
	newNode->rs = NULL;
	
	newNode->label = lab;

	return newNode;
}

void destroyBST(s_BST *node)
{
	if (node != NULL)
	{
		destroyBST(node->ls);
		node->ls = NULL;
		destroyBST(node->rs);
		node->rs = NULL;

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


void makeLs(int lab, s_BST *father)
{
	if (father->ls != NULL)
	{
		error("Attention : on remplace le fils gauche d'un ABR\n"); //Actually more a warning than an error
		destroyBST(father->ls);
	}
	father->ls = makeBST(lab);
}


void makeRs(int lab, s_BST *father)
{
	if (father->rs != NULL)
	{
		error("Attention : on remplace le fils gauche d'un ABR\n"); //Actually more a warning than an error
		destroyBST(father->rs);
	}
	father->rs = makeBST(lab);
}


void insert(int lab, s_BST *node)
{
	if (node == NULL)
		error("Tentative d'insertion dans un BST vide\n");

	if (lab < getLabel(node))
	{
		if (getLs(node) == NULL)
			makeLs(lab, node);
		else
			insert(lab, getLs(node));
	}

	else if (lab > getLabel(node))
	{
		if (getRs(node) == NULL)
			makeRs(lab, node);
		else
			insert(lab, getRs(node));
	}

	else
		error("Tentative d'ajout dans un BST d'un element redondant\n");
}


s_sadPair seekAndDestroy(s_BST *node)
{
	s_sadPair res;
	if (getRs(node) != NULL)
	{
		res = seekAndDestroy(getRs(node));
		node->rs = res.node;
		res.node = node;
	}


	else
	{
		res.node = getLs(node);
		res.label = getLabel(node);
	}

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

	else if (lab == getLabel(node)) // It is THE node to suppress
	{
		if (getLs(node) == NULL)
		{
			newNode = getRs(node);

			node->rs = NULL;
			destroyBST(node);
		}

		else if (getRs(node) == NULL)
		{
			newNode = getLs(node);

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
		if (lab < getLabel(node))
			node->ls = delete(lab, getLs(node));
	
		else //(lab > getLabel(node))
			node->rs = delete(lab, getRs(node));
	}
		return newNode;
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
		printf("%d ", getLabel(node));
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
	printf("==> %d\n", size);
	bool isBST = true;
	int last = list[0];

	int i = 0;
	for (i = 0; i < size; i++)
	{
		printf("%d ", list[i]);
		isBST = isBST && (list[i] >= last);
		last = list[i];
	}
	printf("==> %s", isBST ? "C'est bien un ABR ! =)\n" : "Ce n'est pas un ABR ! =(\n");
}


