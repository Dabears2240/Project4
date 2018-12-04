/////////////////////////////////////////////////
//
//	File:   537malloc.c
//
//	CS537 Program 4
//	Author: Mike Tuchler
//		Drew Kyser
//
/////////////////////////////////////////////////

#include "537malloc.h";

void* malloc537(size_t size) {
	// size 0 case
	if (size == 0) {
		printf("Warning: memory allocated of size 0.\n");
	}
	// negative size
	if (size < 0) {
		printf("Error: memory allocated of negative size.\n");
		exit(-1);
	}
	// actual memory allocation
	void* addr = malloc(size);
	Node* node = find(addr);
	if (node == NULL) {
		node = initNode(addr, size);
		insert(node);
		// check space
	}
	else if (node->freed) {
		node->freed = 0;
		size_t oldsize = node->size;
		node->size = size;
		// check space
	}
	else {
		printf("Error: memory address not available (%p)\n", addr);
		exit(-1);
	}

	// check if there isSpace
	isSpace(node);
	// with that space, coalesce
	coalesce(node);

	return node;
}

// frees the given pointer and updates the tree
// throws a variety of critical errors
void free537(void *ptr) {
	// null argument
	if (ptr == NULL) {
		printf("Error: free537 called on NULL pointer.\n");
		exit(-1);
	}
	Node* node = find(ptr);
	// fails to find, that memory not allocated
	if (node == NULL) {
		printf("Error: free537 called on a pointer that was not given with malloc.\n");
		printf("It was either not allocated, or not the first byte of a mem block.\n");
		exit(-1);
	}
	// double free
	if (node->freed == 1) {
		printf("Error: double free on address (%p)\n", ptr);
		exit(-1);
	}

	// set that node to free
	node->freed = 1;
	// actual free
	free(ptr);

	return;
}

void* realloc537(void *ptr, size_t size) {
	//if ptr is null, call malloc
	if (ptr == NULL){
		malloc537(size);
	}
	
	//if size is 0 and ptr is not null, follow free above
	else if (ptr != NULL && size == 0){
		free(ptr);
	}
	
	//else, find tuple containing addr and remove it, then re-allocate
	else{
		Node* node = find(ptr);
		if (node != NULL){
			delete(node);
			free(node);
			void* addr = realloc(ptr, size);
			node = initNode(addr, size);
			isSpace(node);
			coalesce(node);
			insert(node);
		}
	}
	
	return NULL;
}

//checks to see if a memory location/size are within a range allocated by malloc and not free'd
void memcheck537(void* ptr, size_t size) {
	Node* node = find(ptr);
	
	//if find() returns a node that is not null and not freed, we're good!
	if (node!= NULL && !node->freed){
		return;
	}	
	
	//if node returns NULL, we need to figure out if it is due to no existing node containing ptr, or if ptr is contained
	//in node but doesn't match node->addr
	else{
			Node* root = getRoot();
			i	
	}
	return;
}

// called on a node that was just inserted into the tree/modified
// traverses forward and backward to see if it interferes with another alloc'd block
// note: none of this should happen if malloc, and our functions, work
void isSpace(Node* node) {
	if (node == NULL) {
		exit(-1);
	}
	void* addr = node->addr;
	size_t size = node->size;
	// check backwards
	Node* prev = findPrev(node);
	Node* next = findNext(node);
	// first address case
	if (prev == NULL) {
		// we good
	}
	// left side overlap case
	else if ((prev->addr + prev->size) > addr) {
		if (!prev->freed) {
			printf("Error: memory overlaps with previous block\n");
			exit(-1);
		}
	}

	if (next == NULL) {
		// we good
	}
	// right side overlap case
	else if ((addr + size) > next->addr) {
		if (!next->freed) {
			printf("Error: memory overlaps with next block\n");
			exit(-1);
		}
		// check for further overlap
		while ((addr + size) > (next->addr + next->size)) {
			next = findNext(next);
			if (!next->freed) {
				printf("Error: memory overlaps with next block\n");
				exit(-1);
			}
		}
	}
	return;
}

// called on a node with enough space
// looks to next blocks to combine them into one
// includes left and right splits
void coalesce(Node* node) {
	if (node == NULL) {
		printf("Error: coalesce called on NULL\n");
		exit(-1);
	}
	// if there's enough space in the current block
	Node* next = findNext(node);
	if (next != NULL) {
		while ((node->addr + node->size) > (next->addr)) {
			// if is surpasses the next block
			if ((node->addr + node->size) > (next->addr + next->size)) {
				Node* overlapped = next;
				next = findNext(next);
				delete(overlapped);
			}
		}
		// it's deleted all the completely overlapped nodes
		// split that last one if applicable
		next->size = ((size_t)next->addr + next->size) - ((size_t)node->addr + node->size);
		next->addr = node->addr + node->size;
	}
	// finally, left split
	Node* prev = findPrev(node);
	if (prev != NULL) {
		// we checked the validity of the cast
		prev->size = (size_t)node->addr - (size_t)prev->addr;
	}
	return;
}
