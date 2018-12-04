/////////////////////////////////////////////////
//
//	File:	RBtree.c
//
//	CS537 Project 4
//	Author:	Mike Tuchler
//		Drew Kyser
//
/////////////////////////////////////////////////

#include "RBtree.h"

Node* root;

// Getter function so the root can be set in the
// implementation
Node* getRoot() {
	return root;
}

// Initializes a node (red and !freed)
Node* initNode(void* addr, size_t size) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->addr = addr;
	newNode->size = size;
	newNode->red = 1;
	newNode->freed = 0;
	return newNode;
}

// Inserts a node into the tree as any BST insertion, then rebalances
void insert(Node* newNode) {
	// root
	if (root == NULL) {
		root = newNode;
		root->red = 0;
		root->freed = 0;
		return;
	 }

	// not root
	Node* pptr = NULL;
	int left;
	Node* ptr = root;
	while (ptr != NULL) {
		// equal
		if (ptr->addr == newNode->addr) {
			//might be free
		}
		// compare addresses
		else if (ptr->addr > newNode->addr) {
			// send left
			pptr = ptr;
			ptr = ptr->left;
			left = 1;
		}
		else {
			// send right
			pptr = ptr;
			ptr = ptr->right;
			left = 0;
		}
	}

	if (left)
		pptr->left = newNode;
	else
		pptr->right = newNode;
	ptr = newNode;
	ptr->parent = pptr;
	ptr->red = 1;
	ptr->freed = 0;

	// balancing the tree
	// determine color of added node by looking at uncle/parent
	rebalanceInsert(ptr);

	return;
}

// On an insertion to a RB tree, a rebalance is required
// to maintain the balanced tree property.
//
// this is also called in rebalanceDelete for a few cases
void rebalanceInsert(Node* node) {
        // root check
        if (node == root) {
                return;
        }
        // child of root check
        if (node->parent == root) {
                return;
        }
        // black parent check (w/o double black)
        if (!isRed(node->parent)) {
                return;
        }

        // family pointers
        Node* parent = node->parent;
        Node* gparent = parent->parent;
        Node* uncle = NULL;
        if (gparent != NULL){
                if (gparent->left == parent)
                        uncle = gparent->right;
                else if (gparent->right == parent)
                        uncle = gparent->left;
        }

	// recursive rebalance
        // check uncle color
        if (isRed(uncle)) {
                parent->red = 0;
                uncle->red = 0;
                gparent->red = 1;
                // recursive on grandparent
                rebalanceInsert(gparent);
        }
        else {
                // uncle is black
                // FOUR CASES

                // LEFT LEFT CASE
                if (parent == gparent->left && node == parent->left) {
                        rotateRight(gparent);
                        // colors
                        int red = gparent->red;
                        gparent->red = parent->red;
                        parent->red = red;
                }
                // LEFT RIGHT CASE
                else if (parent == gparent->left && node == parent->right) {
                        rotateLeft(parent);
                        rotateRight(gparent);
                        // colors
                        int red = gparent->red;
                        gparent->red = node->red;
                        node->red = red;
                }
                // RIGHT RIGHT CASE
                else if (parent == gparent->right && node == parent->right) {
                        rotateLeft(gparent);
                        // colors
                        int red = gparent->red;
                        gparent->red = parent->red;
                        parent->red = red;
                }
                // RIGHT LEFT CASE
                else {
                        rotateRight(parent);
                        rotateLeft(gparent);
                        // colors
                        int red = gparent->red;
                        gparent->red = node->red;
                        node->red = red;
                }
                rebalanceInsert(gparent);
        }

        root->red = 0;

        return;
}

void delete(Node* node) {
	// standard BST removal
	// case 1: no children
	if (node->left == NULL && node->right == NULL) {
		// root checking
		if (node == root) {
			root = NULL;
			return;
		}

		if (node->parent->left == node)
			node->parent->left = NULL;
		else
			node->parent->right = NULL;
		
		// rebalance if a black leaf was removed
		if (!isRed(node)) {
			node->red = -1;
			rebalanceDelete(node);
		}
		return;
	}
	// case 2: one child
	else if (node->left == NULL || node->right == NULL) {
		// get child ptr
		Node* child;
		if (node->left == NULL)
			child = node->right;
		else
			child = node->left;
		
		// root checking
		if (node == root){
			root = child;
			child->parent = NULL;
			child->red = 0;
			return;
		}

		// set parent's child to node's child
		if (node->parent->left == node) {
			node->parent->left = child;
			child->parent = node->parent;
		}
		else {
			node->parent->right = child;
			child->parent = node->parent;
		}
		
		// rebalance if neither node nor child are red
		if (!isRed(node) && !isRed(child)) {
			child->red = -1;
			rebalanceDelete(child);
		}
		else {
			child->red = 0;
		}
		return;
	}
	// case 3: two children
	else {
		// finds leftmost node of right subtree
		Node* leftmost = node->right;
		while (leftmost->left != NULL) {
			leftmost = leftmost->left;
		}
		// swap node and leftmost
		// by swapping parents
		/*Node* swp = node->parent;
		node->parent = leftmost->parent;
		leftmost->parent = swp;
		if (leftmost->parent != NULL) {
			if (leftmost->parent->left == node)
				leftmost->parent->left = leftmost;
			else
				leftmost->parent->right = leftmost;
		}
		if (node->parent->left == node)
			node->parent->left = node;
		else
			node->parent->right = node;
		// then swapping children
		leftmost->left = node->left;
		leftmost->left->parent = leftmost;
		node->left = NULL;
		swp = node->right;
		node->right = leftmost->right;
		if (swp != leftmost)	// for spec. case where leftmost is node->right
			leftmost->right = swp;
		else
			leftmost->right = node;
		if (node->right != NULL)
			node->right->parent = node;
		leftmost->right->parent = leftmost;*/

		// INSTEAD, WE CAN SWAP VALUES (not color)
		// addr swap
		void* addrswap = leftmost->addr;
		leftmost->addr = node->addr;
		node->addr = addrswap;
		// size swap
		size_t sizeswap = leftmost->size;
		leftmost->size = node->size;
		node->size = sizeswap;
		// freed swap
		int freedswap = leftmost->freed;
		leftmost->freed = node->freed;
		node->freed = freedswap;

		// recursive delete call
		delete(leftmost);
		return;
	}
}

// function for rebalancing and recoloring in the delete case
// node is the double black (child, or deleted node if NULL)
void rebalanceDelete(Node* node) {
	// complex case: both node and child are black
	// we can assume node has a sib
	if (node == root) {
		node->red = 0;
		return;
	}

	// get relations (child is what replaced node)
	Node* parent = node->parent;
	Node* child = (node->left == NULL) ? node->right : node->left;
	Node* sib = (parent->left == child) ? parent->right : parent->left;
	Node* lnephew = (sib != NULL) ? sib->left : NULL;
	Node* rnephew = (sib != NULL) ? sib->right : NULL;

	// if sib is black and a neph is red
	if (!sib->red && (isRed(lnephew) || isRed(rnephew))) {
		// FOUR CASES
		// NO RECURSION: WE SOLVE THE DOUBLE BLACK HERE
		// LEFT LEFT (sib is a left child and its left child or both is red)
		if ((sib->parent->left == sib) && isRed(lnephew)) {
			printf("LL entered\n");
			rotateRight(parent);
			// colors
			doubleBlack(node, 0);
		}
		// LEFT RIGHT
		else if ((sib->parent->left == sib) && isRed(rnephew)) {
			printf("LR entered\n");
			// 1st rotation
			rotateLeft(sib);
			// colors
			rnephew->red = 0;
			sib->red = 1;
			// 2nd rotation
			rotateRight(parent);
			// colors
			doubleBlack(node, 0);
		}
		// RIGHT RIGHT
		else if ((sib->parent->right == sib) && isRed(rnephew)) {
			printf("RR entered\n");
			rotateLeft(parent);
			// colors
			doubleBlack(node, 0);
		}
		// RIGHT LEFT
		else {
			printf("RL entered\n");
			// 1st rotation
			rotateRight(sib);
			// colors
			lnephew->red = 0;
			sib->red = 1;
			// 2nd rotation
			rotateLeft(parent);
			// colors
			doubleBlack(node, 0);
		}
	}
	// if sib is black and both nephs are black
	else if (!isRed(sib)) {
		// THIS CASE IS RECURSIVE: DOUBLE BLACK CAN PROPOGATE
		doubleBlack(node, 1);
	}
	// if sib is red
	else {
		// LEFT
		if (sib->parent->left == sib) {
			rotateRight(parent);
			int swp = sib->red;
			sib->red = parent->red;
			parent->red = swp;
			rebalanceDelete(node);
		}
		// RIGHT
		else {
			rotateLeft(parent);
			int swp = sib->red;
			sib->red = parent->red;
			parent->red = swp;
			rebalanceDelete(node);
		}
	}

}

// solves a double black node
// resolving a double black requires knowing whether you care
// about the sibling or the uncle. Each has 2 cases, depending on the
// parent, but you otherwise don't know anything about the tree unless you
// pass it in. I may be mistaken though.
void doubleBlack(Node* node, int casenum) {
	// root check
	if (node == root) {
		node->red = 0;
		return;
	}
	
	Node* parent = node->parent;

	// cares about the uncle
	if (casenum == 0) {
		// family
		Node* gparent = parent->parent;
		Node* uncle = (gparent->right != parent) ? gparent->right : gparent->left;

		node->red = 0;
                // case depends on parent
                if (isRed(parent)) {
                        parent->red = 0;
                        uncle->red = 0;
                        gparent->red = 1;
                        // rebalance/recolor for gparent
                        rebalanceInsert(gparent);
                }
                else {
                        uncle->red = 0;
                }
                return;
	}
	// cares about the sibling
	else if (casenum == 1) {
		// family relations
		Node* child = (node->left != NULL) ? node->left : node->right;
		Node* sib = (parent->left != child) ? parent->left : parent->right;

		// recolor and move up double black
		node->red = 0;
		sib->red = 1;
		if (isRed(parent)) {
			parent->red = 0;
		}
		else {
			parent->red = -1;
			// determine double-black case
			rebalanceDelete(parent);
		}
		return;
	}
}
	

// called on a node to recolor recursively
// compares it to it's uncle

// called on the top node of the rotation, moving it
// to the position of its right child
void rotateRight(Node* node) {
	// u and p named from an online diagram
	Node* p = node->left;
	Node* parent = node->parent;

	// set new root
	if (root == node)
		root = p;
	
	// moving right child of p
	node->left = p->right;
	if (node->left != NULL)
		node->left->parent = node;
	// setting parent of p
	p->parent = parent;
	if (parent != NULL && parent->left == node)
		parent->left = p;
	else if (parent != NULL && parent->right == node)
		parent->right = p;
	// set right child of p to node
	p->right = node;
	node->parent = p;

	return;
}

// called on the top node of the rotation, moving it
// to the position of its left child
void rotateLeft(Node* node) {
	Node* p = node->right;
	Node* parent = node->parent;

	// set new root
	if (root == node)
		root = p;

	// moving left child of p to right child of node
	node->right = p->left;
	if (node->right != NULL)
		node->right->parent = node;
	// setting parent of p
	p->parent = parent;
	if (parent != NULL && parent->left == node)
		parent->left = p;
	else if (parent != NULL && parent->right == node)
		parent->right = p;
	// set left child of p to node
	p->left = node;
	node->parent = p;

	return;
}

// function returns the color
// implicit NULL handling -- NULL node is black
int isRed(Node* node) {
	if (node == NULL)
		return 0; // black
	else
		return node->red;
}

// gets the level of the node (0 is root)
// mostly for printing purposes
int getLevel(Node* node) {
	if (node == NULL)
		return -1;
	int count = 0;
	Node* ptr = node;
	while (ptr->parent != NULL) {
		ptr = ptr->parent;
		count++;
	}
	return count;
}

// function to find a node in a tree, from it's address
// returns the node on success
// returns NULL on failure
Node* find(void* addr) {
	Node* ptr = root;
	while (ptr != NULL) {
		if (addr == ptr->addr) {
			return ptr;
		}
		else if (addr > ptr->addr) {
			ptr = ptr->right;
		}
		else {
			ptr = ptr->left;
		}
	}
	return NULL;
}

// for range queries, finds the arithmetic next node in the tree
// returns the node next to the argument, or NULL if it's furthest right
Node* findNext(Node* node) {
	// null check
	if (node == NULL) {
		printf("findNext called on NULL node\n");
		exit(-1);
	}

	Node* next;

	// find that next node
	// is there a right child?
	if (node->right != NULL) {
		// find the leftmost node of right subtree
		next = node->right;
		while (next->left != NULL)
			next = next->left;
		return next;
	}
	// if there is no right child
	else {
		// three cases here:
		// - node is a left child
		// - node is a right child
		// - node is the root
		Node* parent = node->parent;
		// root case
		if (parent == NULL) {
			// root with no right child is the largest
			return root;
		}
		// node is a left child
		else if (parent->left == node) {
			// next node is it's parent
			return parent;
		}
		// node is a right child
		else {
			// opposite of the case where you find leftmost
			// you're at the largest node of some subtree
			// find the parent of that subtree, i.e. the
			// node that points left to the top of it.
			// If none found, return NULL because you're as
			// far as you're gonna go, man
			next = parent;
			while (1) {
				// no larger node exists
				if (next->parent == NULL) {
					return NULL;
				}
				// if next is a right node
				if (next->parent->left == next)
					return next->parent;
				// try again
				next = next->parent;
			}
		}
	}

	printf("The findNext code is not supposed to go here\n");
	return NULL;
}

// finds the node directly before this node
// same logic as findNext
Node* findPrev(Node* node) {
	if (node == NULL) {
		printf("Error: findPrev called on NULL\n");
		exit(-1);
	}
	Node* prev;
	if (node->left != NULL) {
		prev = node->left;
		while (prev->right != NULL)
			prev = prev->right;
		return prev;
	}
	else {
		Node* parent = node->parent;
		if (parent == NULL)
			return root;
		else if (parent->right == node)
			return parent;
		else {
			prev = parent;
			while(1) {
				if (prev->parent == NULL)
					return NULL;
				if (prev->parent->right == prev)
					return prev->parent;
				prev = prev->parent;
			}
		}
	}
}

// prints the info of the node
// 0xaddr (r/b lvl)
void printNode(Node* node) {
	if (node == NULL) {
		printf("null node print\n");
		return;
	}
	printf("%p (%c %i)\n", (node->addr), (node->red? 'r' : 'b'), getLevel(node));
	return;
}

// recursive function to in-order print the tree
void printTree() {
	if (root == NULL)
		printf("Empty tree\n");
	else
		printTreeHelper(root);
	return;
}
// helper for recursive print
void printTreeHelper(Node* node) {
	// move left
	if (node->left != NULL)
		printTreeHelper(node->left);
	// printing information
	printNode(node);
	// move right
	if (node->right != NULL)
		printTreeHelper(node->right);
	return;

}
