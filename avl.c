#include <stdlib.h>
#include <stdio.h>
#include "avl.h"
#include "cities.h"


//Returns the maximum of two integers
inline int max(int a, int b)
{
	return (a < b) ? b:a;
}



//Makes a new avl node with a label
s_avl *makeAvl(int lab)
{
	s_avl *newNode = malloc(sizeof(*newNode));
	if (newNode == NULL)
		error("Erreur lors de la creation d'un noeud d'un avl\n");

	newNode->ls = NULL;
	newNode->rs = NULL;
	newNode->label = lab;
	newNode->height = 1;
	
	return newNode;
}


//Recursively free all the nodes of the avl tree "node"
void destroyAvl(s_avl *node)
{
	if (node != NULL)
	{
		//Frees the left subtree
		destroyAvl(node->ls);
		node->ls = NULL;

		//Frees the right subtree
		destroyAvl(node->rs);
		node-> rs = NULL;

		//Frees node
		free(node);
	}
}


//Returns the label of a node
int getLabel(s_avl *node)
{
	if (node == NULL)
		error("Tentative de dereferencer un pointeur d'avl NULL (label)\n");

	return node->label;
}

//Returns the left son of a node
s_avl *getLs(s_avl *father)
{
	if (father == NULL)
		error("Tentative de dereferencer un pointeur d'avl NULL (fils gauche)\n");

	return father->ls;
}


//Returns the right son of a node
s_avl *getRs(s_avl *father)
{
	if (father == NULL)
		error("Tentative de dereferencer un pointeur d'avl NULL (fils droit)\n");

	return father->rs;
}




//Computes and returns the height the tree rooted in node
int getHeight(s_avl *node)
{
	if (node == NULL)
		return 0;
	else
		return node->height;
}



//Makes a new left son for the node "father"
void makeLs(int lab, s_avl *father)
{
	if (father->ls != NULL)
	{
		error("Attention : on remplace le fils gauche d'un ABR\n"); 
		destroyAvl(father->ls);
	}
	father-> ls = makeAvl(lab);
}


//Makes a new right son for father
void makeRs(int lab, s_avl *father)
{
	if (father->rs != NULL)
	{
		error("Attention : on remplace le fils droit d'un ABR\n");
		destroyAvl(father->rs);
	}
	father->rs = makeAvl(lab);
}




//Updates the height of node. Useful when changing the
//structure the tree, in particular with rotations
void updateHeight(s_avl *node)
{
	if (node != NULL)
		node->height = 1+max(getHeight(node->ls), getHeight(node->rs));
}



//Creates a new element labeled by "lab" and inserts it in the right place in
//the avl rooted in node. Begins by inserting the new node as a leaf and
//then rebalance the tree.
s_avl *insert(int lab, s_avl *node)
{
	//The new node is now a leaf
	if (node == NULL)
		return makeAvl(lab);

	//Inserts in the left subtree (due to the binary search tree (bst) structure
	else if (lab < node->label)
	{
		node->ls = insert(lab, node->ls);
		//Some rotations may have been done, so we update the height of node
		updateHeight(node->ls);
	}
	
	//Inserts in the right subtree
	else if (lab > node->label)
	{
		node->rs = insert(lab, node->rs);
		updateHeight(node->rs);
	}

	//A BST, by definition, doe not contain the same element more than once
	else
		error("Tentative d'ajout dans un avl d'un element redondant\n");
	updateHeight(node);

	//If the balance factor is out or range => a rebalancing is needed
	if (abs(getHeight(node->ls) - getHeight(node->rs)) > 1)
		node = rebalance(node);

	return node;
}



//An auxiliary fonction used in the deletion: it search for the greatest label
//l_max in node's subtree, and returns a pair {l_max, tree'} where tree' is
//a "copy" of the tree where the node labeled l_max no longer exists
s_sadPair seekAndDestroy(s_avl *node)
{
	s_sadPair res;

	//It isn't the node with the greatest label: the label of his right son is greater
	if (node->rs != NULL)
	{
		res = seekAndDestroy(node->rs);
		node->rs = res.node;

		//Since we deleted a node in node's righ son subtree, it might get unbalanced
		if (abs(getHeight(node->ls) - getHeight(node->rs) > 1))
			node = rebalance(node);
		res.node = node;
	}

	//We have the node with the greatest label
	else
	{
		res.node = node->ls;
		res.label = node->label;

		//We free it directly; no need to use destroyAvl there
		free(node);
	}


	updateHeight(res.node);

	return res;
}





//Deletes the node labeled lab if it exists such a node
s_avl *delete(int lab, s_avl *node)
{
	s_avl *newNode = node;

	//We got to the bottom of the tree without finding the label lab
	if (node == NULL)
	{
		error("Tentative de suppression d'un element qui n'est pas dans l'ABR\n");
		newNode = NULL;
	}

	
	//It is the node to delete
	else if (lab == node->label)
	{
		//The right son can replace the node we want to delete
		if (node->ls == NULL)
		{
			newNode = node->rs;

			node->rs = NULL;
			free(node);
		}

		//The same with the left son
		else if (node->rs == NULL)
		{
			newNode = node->ls;

			node->ls = NULL;
			free(node);
		}


		//We use the SeekAndDestroy function to get a new node (the one with the
		//greatest label in the left subtree. We make a node with this label. The new
		//left son is the left subtree without its greatest labeled node, returned by
		//seekAndDestroy.
		else 
		{
			s_sadPair tmp = seekAndDestroy(node->ls);
			node->ls = tmp.node;
			node->label = tmp.label;
		}
	}

	
	//It is not the node we search for deletion, so we search for in recursively,
	//depending of the current node's label
	else
	{
		if (lab < node->label)
			node->ls = delete(lab, node->ls);
	
		else
			node->rs = delete(lab, node->rs);
	}
	

	//newNode is node if we did not delete node, or else the new node in place.
	//We first update the node's height and the if needed rebalance the tree.
	if (newNode != NULL)
	{
		updateHeight(newNode);
		if (abs(getHeight(newNode->ls) - getHeight(newNode->rs)) > 1)
			newNode = rebalance(newNode);
	}
		return newNode;
}



//Performs a right rotation
s_avl *rightRotation(s_avl *node)
{
	s_avl *ls = node->ls;
	s_avl *lrgs = node->ls->rs;
	
	node->ls = lrgs;
	ls->rs = node;
	
	//Updates the heights in the right order (ls is the new father of node)
	updateHeight(node);
	updateHeight(ls);

	return ls;
}



//Performs a left Rotation
s_avl *leftRotation(s_avl *node)
{
	s_avl *rs = node->rs;
	s_avl *rlgs = node->rs->ls;

	node->rs = rlgs;
	rs->ls = node;

	updateHeight(node);
	updateHeight(rs);
	return rs;
}


//Performs a right double rotation. It consists, in fact, of two single rotations.
//Since we use the single rotations, we don't need to update the heights.
s_avl *rightDoubleRotation(s_avl *node)
{
	node->ls = leftRotation(node->ls);
	node = rightRotation(node);
	return node;
}


//Performs a left double rotation, with two single rotations.
s_avl *leftDoubleRotation(s_avl *node)
{
	node->rs = rightRotation(node->rs);
	node = leftRotation(node);
	return node;
}


//Rebalances the tree rooted in node, through rotations
//If this function is called, it implies that the tree rooted in node is unbalanced.
s_avl *rebalance(s_avl *node)
{
	//The tree is right heavy
	if (getHeight(node->rs) > getHeight(node->ls))
	{
		if (getHeight(node->rs->ls) > getHeight(node->rs->rs))
			node = leftDoubleRotation(node);
		else
			node = leftRotation(node);
	}

	//The tree is left heavy
	else
	{
		if (getHeight(node->ls->rs) > getHeight(node->ls->ls))
			node = rightDoubleRotation(node);
		else
			node = rightRotation(node);
	}

	return node;
}



//Prints a ugly representation of the avl: N(label, leftSon, rightSon), through
//an inorder traversal of the tree. The result is stored into a file.
//It is not beautiful but it is simple, and easy for automated comparisons of trees.
void uglyAvlPrint(s_avl *node, FILE *writeThere)
{
	if (node == NULL)
			fprintf(writeThere, "V");
	else
	{
		fprintf(writeThere, "N(%d, ", node->label);
		uglyAvlPrint(node->ls, writeThere);
		fprintf(writeThere, ", ");
		uglyAvlPrint(node->rs, writeThere);
		fprintf(writeThere, ")");
	}
}


//Writes the labels seen in an inorder traversal of node. The result is stored in
//an array. The function returns a pointer to the next cell to be written in.
int *writeInfix(s_avl *node, int *tab)
{
	if (node != NULL)
	{
		tab = writeInfix(getLs(node), tab);
		*tab = getLabel(node);
		tab =writeInfix(getRs(node), tab+1);
	}
	return tab;
}



//Recursively computes the number of nodes of an avl and returns it
int avlSize(s_avl *node)
{
	if (node == NULL)
		return 0;
	else
		return 1 + avlSize(getLs(node)) + avlSize(getRs(node));
}



//A tree is a avl if and only if the inorder traversal of a tree returns a sorted list.
bool isThisAnAvl(s_avl *node)
{
	int size = avlSize(node);
	bool isAvl = true;
	
	if (size > 0)
	{
		int *list = malloc(size * sizeof(*list));
		//Computes the inorder traversal
		writeInfix(node, list);
		int last = list[0];

		int i = 0;
		for (i = 0; i < size; i++)
		{
			//> instead of >=: there must not be two nodes with the same label
			isAvl = isAvl && (list[i] > last);
			last = list[i];
		}

		free(list);
	}

	return isAvl;
}


//Used to debug the code: prints the heights of every node in the tree
void printHeights(s_avl *root)
{
	printf("Test de la mise a jour des hauteurs :\n");
	int size = avlSize(root);

	s_avl *queue = malloc(size*sizeof(*queue));
	
	if (size > 0)
	{
		queue[0] = *root;
		int top = 1;
		int bottom = 0;
		s_avl cur;

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


//Tests if the tree is balanced, ie if no node in the tree has a balance factor
//out of the range [-1;1]
bool isThisBalanced(s_avl *node)
{
	if (node == NULL)
		return true;
	
	else
		return isThisBalanced(node->ls) && isThisBalanced(node->rs) 
				  && (abs(getHeight(node->ls) - getHeight(node->rs)) <= 1);
}

