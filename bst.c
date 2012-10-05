#include <stdlib.h>
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
