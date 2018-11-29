#ifndef RBTREE_H
#define RBTREE_H

typdef struct node {
	void* addr;
	size_t size;
	int red;
	int freed;
} node;

#endif
