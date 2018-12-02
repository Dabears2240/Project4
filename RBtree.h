#ifndef RBTREE_H
#define RBTREE_H

#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
	void* addr;
	size_t size;
	int red;
	int freed;
	struct Node *parent, *left, *right;
} Node;

//const int TREE_SIZE = 1024;

Node* getRoot();
Node* initNode(void* addr, size_t size);
void insert(Node* node);
void delete(Node* node);
void rotateRight(Node* node);
void rotateLeft(Node* node);
void rebalance(Node* node);
Node* find(void* addr);
void printTree();
void printTreeHelper(Node* node);

#endif
