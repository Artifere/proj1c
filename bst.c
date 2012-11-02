#include <stdlib.h>
#include <stdio.h>
#include "bst.h"
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
//crée un arbre binaire de recherche avec un seul élément, passé en argument.

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
//Libère l'espace mémoire alloué à un arbre.


int getLabel(s_BST *node)
{
	if (node == NULL)
		error("Tentative de dereferencer un pointeur d'BST NULL (label)\n");

	return node->label;
}
//Prend en argument un arbre, et renvoie l'étiquette de sa racine.

s_BST *getLs(s_BST *father)
{
	if (father == NULL)
		error("Tentative de dereferencer un pointeur d'BST NULL (fils gauche)\n");

	return father->ls;
}
//Prend en argument un arbre, et renvoie son sous arbre gauche.

s_BST *getRs(s_BST *father)
{
	if (father == NULL)
		error("Tentative de dereferencer un pointeur d'BST NULL (fils droit)\n");

	return father->rs;
}
//Prend en argument un arbre, et renvoie son sous arbre droit.

int getHeight(s_BST *node)
{
	if (node == NULL)
		return 0;
	else
		return node->height;
}
//Prend en argument un arbre, et renvoie sa hauteur.


void makeLs(int lab, s_BST *father)
{
	if (father->ls != NULL)
	{
		error("Attention : on remplace le fils gauche d'un ABR\n"); //Actually more a warning than an error
		destroyBST(father->ls);
	}
	father-> ls = makeBST(lab);
}
//Prend en argument un entier et un arbre, et remplace le sous-arbre gauche de l'arbre(pouvant être vide) par l'arbre binaire ne comportant qu'un élément, l'entier passé en paramètre.


void makeRs(int lab, s_BST *father)
{
	if (father->rs != NULL)
	{
		error("Attention : on remplace le fils droit d'un ABR\n"); //Actually more a warning than an error
		destroyBST(father->rs);
	}
	father->rs = makeBST(lab);
}
//Prend en argument un entier et un arbre, et remplace le sous-arbre droit de l'arbre(pouvant être vide) par l'arbre binaire ne comportant qu'un élément, l'entier passé en paramètre.


void updateHeight(s_BST *node)
{
	if (node != NULL)
		node->height = 1+max(getHeight(node->ls), getHeight(node->rs));
}
//Prend un arbre en argument et renvoie sa hauteur, calculée arithmétiquement et non celle stockée dans la structure d'arbre.


s_BST *insert(int lab, s_BST *node)
{
	if (node == NULL)
		return makeBST(lab);

	else if (lab < node->label)
	{
		/*if (node->ls == NULL)
			node->ls = insert(lab, NULL);
		else*/
			node->ls = insert(lab, node->ls);
		updateHeight(node->ls);//On doit recalculer les hauteurs stockées dans les structures.
	}

	else if (lab > node->label)
	{
		/*if (node->rs == NULL)
			node->rs = insert(lab, NULL);
		else*/
			node->rs = insert(lab, node->rs);

		updateHeight(node->rs);
	}

	else
		error("Tentative d'ajout dans un BST d'un element redondant\n");
	updateHeight(node);

	if (abs(getHeight(node->ls) - getHeight(node->rs)) > 1)
		node = rebalance(node);//si l'arbre est déséquilibré après insertion, on le rééquilibre.
	return node;
}
//Insère un élément dans un arbre binaire de recherche.



s_sadPair seekAndDestroy(s_BST *node)
{
	s_sadPair res;
	if (node->rs != NULL)
	{
		res = seekAndDestroy(node->rs);
		node->rs = res.node;
		if (abs(getHeight(node->ls) - getHeight(node->rs) > 1))
			node = rebalance(node);
		res.node = node;
	}


	else
	{
		res.node = node->ls;
		res.label = node->label;
		free(node);
	}

	updateHeight(res.node);

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
			free(node);
		}

		else if (node->rs == NULL)
		{
			newNode = node->ls;

			node->ls = NULL;
			free(node);
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
	
	if (newNode != NULL)
	{
		updateHeight(newNode);
		if (abs(getHeight(newNode->ls) - getHeight(newNode->rs)) > 1)
			newNode = rebalance(newNode);
	}
		return newNode;
}
//Supprime un élément dans un arbre binaire de recherche.



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
	//printf("Right rotation done.\n");

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
	//printf("Left rotation done.\n");
	return rs;
}

//For the double rotations, since we use simple ones to do them, no need to update their heights
s_BST *rightDoubleRotation(s_BST *node)
{
	node->ls = leftRotation(node->ls);
	node = rightRotation(node);
	//updateHeight(node);
	//printf("==>Right double rotation done.\n");
	return node;
}

s_BST *leftDoubleRotation(s_BST *node)
{
	node->rs = rightRotation(node->rs);
	node = leftRotation(node);
	//updateHeight(node);
	//printf("==>Left double rotation done.\n");
	return node;
}


s_BST *rebalance(s_BST *node)
{
	//For debugging pourposes only, to be removed when all work
	if (getHeight(node->rs) > getHeight(node->ls))
	{
		if (getHeight(node->rs->ls) > getHeight(node->rs->rs))
			node = leftDoubleRotation(node);
		else
			node = leftRotation(node);
	}
		else
	{
		if (getHeight(node->ls->rs) > getHeight(node->ls->ls))
			node = rightDoubleRotation(node);
		else
			node = rightRotation(node);
	}
	//updateHeight(node);
	return node;
}




void uglyBSTPrint(s_BST *node, FILE *writeThere)
{
	if (node == NULL)
			fprintf(writeThere, "V");
	else
	{
		fprintf(writeThere, "N(%d, ", node->label);
		uglyBSTPrint(node->ls, writeThere);
		fprintf(writeThere, ", ");
		uglyBSTPrint(node->rs, writeThere);
		fprintf(writeThere, ")");
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
bool isThisABst(s_BST *node)
{
	int size = BSTSize(node);
	bool isBST = true;
	
	//Tests to do... NULL...
	if (size > 0)
	{
		int *list = malloc(size * sizeof(*list));
		writeInfix(node, list);
		//printf("==> %d\n", size);
		int last = list[0];

		int i = 0;
		for (i = 0; i < size; i++)
		{
		//printf("%d ", list[i]);
			isBST = isBST && (list[i] >= last);
			last = list[i];
		}

		free(list);
	}
	return isBST;
}


//Fausse file, prend de la place pour rien, mais simple et efficace
void printHeights(s_BST *root)
{
	printf("Test de la mise a jour des hauteurs :\n");
	int size = BSTSize(root);

	s_BST *queue = malloc(size*sizeof(*queue));
	
	if (size > 0)
	{
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

		free(queue);
	}
}	


bool isThisBalanced(s_BST *node)
{
	if (node == NULL)
		return true;
	
	else
		return isThisBalanced(node->ls) && isThisBalanced(node->rs) 
				  && (abs(getHeight(node->ls) - getHeight(node->rs)) <= 1);
}

