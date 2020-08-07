#ifndef _RB_TREE_H_
#define _RB_TREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int Element;

typedef struct rb_node{
	Element data;
	int bal;
	bool color; // color red (1), black (0)
	struct rb_node* filsG;
	struct rb_node* filsD;
}Node;

typedef Node* pt_Arbre;
typedef pt_Arbre rb_tree;

/*-- Functions --*/

rb_tree createTree (Element x);
rb_tree createNode (Element x, bool color);
int hauteur (rb_tree arbre);
void insertNode (rb_tree* tree, rb_tree node);

#endif
