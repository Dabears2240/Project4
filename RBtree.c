/////////////////////////////////////////////////
//
//	File:	RBtree.c
//
//	CS537 Project 4
//	Author:	Mike Tuchler
//		Drew Kyser
//
/////////////////////////////////////////////////

#include "RBtree.h";

Node* tree[TREE_SIZE];
Node* root;

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
	ptr->red = 1;
	ptr->freed = 0;

	// balancing the tree
	// determine color of added node by looking at uncle/parent
	rebalance(ptr);

	return;
}

void delete(Node* node) {
	Node* removed = node;
	Node* child;
	int rmcase = 0;
	// standard BST removal
	// case 1: no children
	if (node->left == NULL && node->right == NULL) {
		if (node->parent->left == node)
			node->parent->left == NULL;
		else
			node->parent->right == NULL;
		rmcase = 1;
	}
	// case 2: one child
	else if (node->left == NULL || node->right == NULL) {
		// get child ptr
		if (node->left == NULL)
			child = node->right;
		else
			child = node->left;

		// set parent's child to node's child
		if (node->parent->left == node) {
			node->parent->left = child;
			child->parent = node->parent;
		}
		else {
			node->parent->right = child;
			child->parent = node->parent;
		}
		rmcase = 2;
	}
	// case 3: two children
	else {
		Node* leftmost = node->right;
		while (leftmost->left != NULL) {
			leftmost = leftmost->left;
		}
		// swap node and leftmost
		// by swapping parents
		Node* swp = node->parent;
		node->parent = leftmost->parent;
		leftmost->parent = swp;
		if (leftmost->parent->left == node)
			leftmost->parent->left = leftmost;
		else
			leftmost->parent->right = leftmost;
		node->parent->left = node;
		// then swapping children
		leftmost->left = node->left;
		leftmost->left->parent = leftmost;
		node->left = NULL;
		swp = node->right;
		node->right = leftmost->right;
		leftmost->right = swp;
		if (node->right != NULL)
			node->right->parent = node;
		leftmost->right->parent = leftmost;
		// recursive delete call
		delete(node);
		return;
	}

	// recoloring and rebalancing
	// simple case: either node or child is red
	int simple = 1;
	if (rmcase == 1 && node->red) {
		// do nothing
	}
	else if (rmcase == 2) {
		if (node->red || child->red) {
			child->red = 0;
		}
		else {
			simple = 0;
		}
	}

	if (simple)
		return;

	// complex case: both node and child are black
	child->red = -1; // double black
	Node* parent = child->parent;
	Node* sib;
	if (child->parent->left = child)
		sib = parent->right;
	else
		sib = parent->left;
	Node* lnephew = NULL;
	Node* rnephew = NULL;
	int nephcolor[2] = {0, 0};
	if (sib->left != NULL) {
		lnephew = sib->left;
		nephcolor[0] = lnephew->red;
	}
	if (sib->right != NULL) {
		rnephew = sib->right;
		nephcolor[1] = rnephew->red;
	}
	// if sib is black and a neph is red
	if (!sib->red && (nephcolor[0] || nephcolor[1])) {
		// FOUR CASES (LEFT/RIGHT LEFT/RIGHT)
		// LEFT LEFT (sib is a left child and its left child or both is red
		if ((sib->parent->left == sib) && nephcolor[0] == 1) {




}


void rebalance(Node* node) {
	if (node == root) {
		return;
	}

	// family pointers
	Node* parent = node->parent;
	Node* gparent = parent->parent;
	Node* uncle;
	if (gparent->left == parent)
		uncle = gparent->right;
	else if (gparent->right == parent)
		uncle = gparent->left;


	// recursive rebalance
	// check uncle color
	if (uncle->red) {
		// uncle is red!
		parent->.red = 0;
		uncle->red = 0;
		gparent->red = 1;
		// recursive on grandparent
		rebalance(gparent);
	}
	else {
		// uncle is black
		// FOUR CASES
		Node* swp;
		// LEFT LEFT CASE
		if (parent == gparent->left && node == parent->left) {
			gparent->left = parent->right;
			gparent->left->parent = gparent;
			parent->right = gparent;
			parent->parent = gparent->parent;
			if (parent->parent->left == gparent)
				parent->parent->left = parent;
			else
				parent->parent->right = parent;
			gparent->parent = parent;
			// colors
			int red = gparent->red;
			gparent->red = parent->red;
			parent->red = red;
		}
		// LEFT RIGHT CASE
		else if (parent == gparent->left && node == parent->right) {
			// swap parent and node
			node->parent = gparent;
			gparent->left = node;
			swp = node->left;
			node->left = parent;
			parent->right = swp;
			parent->parent = node;
			// left left again
			if (gparent->parent->left == gparent)
				gparent->parent->left = node;
			else
				gparent->parent->right = node;
			node->parent = gparent->parent;
			gparent->left = node->right;
			gparent->left->parent = gparent;
			node->right = gparent;
			gparent->parent = node;
			// colors
			int red = gparent->red;
			gparent->red = node->red;
			node->red = red;
		}
		// RIGHT RIGHT CASE
		else if (parent == gparent->right && node == parent->right) {
			if (gparent->parent->left == gparent)
				gparent->parent->left = parent;
			else
				gparent->parent->right = parent;
			parent->parent = gparent->parent;
			gparent->right = parent->left;
			gparent->right->parent = gparent;
			gparent->parent = parent;
			parent->left = gparent;
			// colors
			int red = gparent->red;
			gparent->red = parent->red;
			parent->red = red;
		}
		// RIGHT LEFT CASE
		else {
			// swap node and parent
			parent->left = node->right;
			parent->left->parent = parent;
			node->right = parent;
			parent->parent = node;
			node->parent = gparent;
			gparent->right = node;
			// right right again
			if (gparent->parent->left == gparent)
				gparent->parent->left = node;
			else
				gparent->parent->right = node;
			node->parent = gparent->parent;
			gparent->parent = node;
			gparent->right = node->left;
			gparent->right->parent = gparent;
			node->left = gparent;
			// colors
			int red = gparent->red;
			gparent->red = node->red;
			node->red = red;
		}
	}	

	return;
}
