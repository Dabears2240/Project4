#ifndef RBTREE_H
#define RBTREE_H

typdef struct Node {
	void* addr;
	size_t size;
	int red;
	int freed;
	Node *parent, *left, *right;
} Node;

const int TREE_SIZE = 1024;

void insert(Node* node);
void delete(Node* node);
void rebalance(Node* node);

#endif
