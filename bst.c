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
//create a BST, the label of the node being the integer lab.

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
//free the memory space used by a tree.


int getLabel(s_BST *node)
{
	if (node == NULL)
		error("Tentative de dereferencer un pointeur d'BST NULL (label)\n");

	return node->label;
}
//return the root of a tree.

s_BST *getLs(s_BST *father)
{
	if (father == NULL)
		error("Tentative de dereferencer un pointeur d'BST NULL (fils gauche)\n");

	return father->ls;
}
//return the left subtree of a tree.

s_BST *getRs(s_BST *father)
{
	if (father == NULL)
		error("Tentative de dereferencer un pointeur d'BST NULL (fils droit)\n");

	return father->rs;
}
//return the right subtree of a tree.

int getHeight(s_BST *node)
{
	if (node == NULL)
		return 0;
	else
		return node->height;
}
//return the height of a tree.


void makeLs(int lab, s_BST *father)
{
	if (father->ls != NULL)
	{
		error("Attention : on remplace le fils gauche d'un ABR\n"); 
		destroyBST(father->ls);
	}
	father-> ls = makeBST(lab);
}
//Replace the leftsubtree of a tree by a node, without any sons, labeled with lab.


void makeRs(int lab, s_BST *father)
{
	if (father->rs != NULL)
	{
		error("Attention : on remplace le fils droit d'un ABR\n");
		destroyBST(father->rs);
	}
	father->rs = makeBST(lab);
}
//Replace the right subtree of a tree by a node, without any sons, labeled with lab.


void updateHeight(s_BST *node)
{
	if (node != NULL)
		node->height = 1+max(getHeight(node->ls), getHeight(node->rs));
}
//update the height memorized into the BST structure by computing it manually.


s_BST *insert(int lab, s_BST *node)
{
	if (node == NULL)
		return makeBST(lab);

	else if (lab < node->label)
	{
		node->ls = insert(lab, node->ls);
		updateHeight(node->ls);//we modified the tree, so we have to update the heights.
	}

	else if (lab > node->label)
	{
		node->rs = insert(lab, node->rs);
		updateHeight(node->rs);
	}

	else
		error("Tentative d'ajout dans un BST d'un element redondant\n");
	updateHeight(node);

	if (abs(getHeight(node->ls) - getHeight(node->rs)) > 1)
		node = rebalance(node);//If the tree isn't balanced, we balance it.
	return node;
}
//Insert a new integer into a BST.



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

	else if (lab == node->label) //we found the right node to delete
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

		else 
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
	
		else
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
//Delete an integer from a BST.


s_BST *rightRotation(s_BST *node)
{
	s_BST *ls = node->ls;
	s_BST *lrgs = node->ls->rs;
	
	node->ls = lrgs;
	ls->rs = node;
	
	updateHeight(node); //First to be updated: it is a ls's son
	updateHeight(ls);

	return ls;
}
//Balance a tree with a single right rotation.

s_BST *leftRotation(s_BST *node)
{
	s_BST *rs = node->rs;
	s_BST *rlgs = node->rs->ls;

	node->rs = rlgs;
	rs->ls = node;

	updateHeight(node);
	updateHeight(rs);
	return rs;
}
//Balance a tree with a single left rotation.

//For the double rotations, since we use simple ones to do them, no need to update their heights
s_BST *rightDoubleRotation(s_BST *node)
{
	node->ls = leftRotation(node->ls);
	node = rightRotation(node);
	return node;
}
//Balance a tree with a double right rotation.

s_BST *leftDoubleRotation(s_BST *node)
{
	node->rs = rightRotation(node->rs);
	node = leftRotation(node);
	return node;
}
//Balance a tree with a double left rotation.


s_BST *rebalance(s_BST *node)
{
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
	return node;
}
//take an unbalanced tree and balance it using the functions decribed just above.




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
//print a BST with N(lbl,lft,rgt), where lbl is the label of the node, lft is the left subtree and rgt the right subtree.


int *writeInfix(s_BST *node, int *tab)
{
	if (node != NULL)
	{
		tab = writeInfix(getLs(node), tab);
		*tab = getLabel(node);
		tab =writeInfix(getRs(node), tab+1);
	}
	return tab;
}
//makes an inorder traversal of a tree.

int BSTSize(s_BST *node)
{
	if (node == NULL)
		return 0;
	else
		return 1 + BSTSize(getLs(node)) + BSTSize(getRs(node));
}
//return the number of nodes in a tree, ie the size of the tree.



// A tree is a BST if and only if the inorder traversal of a tree returns a sorted list.
bool isThisABst(s_BST *node)
{
	int size = BSTSize(node);
	bool isBST = true;
	
	if (size > 0)
	{
		int *list = malloc(size * sizeof(*list));
		writeInfix(node, list);
		int last = list[0];

		int i = 0;
		for (i = 0; i < size; i++)
		{
			isBST = isBST && (list[i] >= last);
			last = list[i];
		}

		free(list);
	}
	return isBST;
}


//used to debug the code.
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
//test if a tree is balanced or note by computing the difference between the height of the left subtree and the height of the right subtree.

