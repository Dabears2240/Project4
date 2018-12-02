// main method

#include "RBtree.h"

int main() {
	int arr[10];
	
	Node* narr[10];
	
	for (int i = 0; i < 10; i++) {
		narr[i] = initNode(arr+i,1);
	}

	insert(narr[4]);
	insert(narr[1]);
	insert(narr[9]);
	insert(narr[0]);
	insert(narr[7]);
	insert(narr[2]);
	insert(narr[3]);
	insert(narr[5]);
	insert(narr[6]);
	insert(narr[8]);

	printTree();

	return 0;
}
