// main method

#include "RBtree.h"

void insertTest() {
	int arr[100];
	Node* narr[100];
	for (int i = 0; i < 100; i++) {
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
	return;
}

void simpleDelete() {
	int arr[100];
	Node* narr[100];
	for (int i = 0; i < 100; i++) {
		narr[i] = initNode(arr+i,1);
	}
	insert(narr[1]);
	insert(narr[2]);
	insert(narr[3]);
	printTree();
	delete(narr[2]);
	printf("~~deletion~~\n");
	printTree();
	return;
}

void deleteNephR(int c) {
	// change target for different cases
	int target1, target2;
	switch (c) {
	       	case 0:	// LL
			target1 = 45;
			target2 = 40;
			break;
		case 1: // RR
			target1 = 15;
			target2 = 20;
			break;
		case 2: // LR
			target1 = 75;
			target2 = 80;
			break;
		case 3:	// RL
			target1 = 65;
			target2 = 60;
			break;
	}
	int arr[100];
	Node* n[100];
	for (int i = 0; i < 100; i++)
		n[i] = initNode(arr+i,1);
	insert(n[50]);
	insert(n[30]);
	insert(n[70]);
	insert(n[20]);
	insert(n[40]);
	insert(n[60]);
	insert(n[80]);
	insert(n[15]);
	insert(n[45]);
	insert(n[65]);
	insert(n[75]);
	printTree();
	printf("~~deleting %i, %i~~\n", target1, target2);
	delete(n[target1]);
	delete(n[target2]);
	printTree();
	return;
}

void deleteNephB() {
        int arr[100];
	Node* n[100];
	for (int i = 0; i < 100; i++)
		n[i] = initNode(arr+i,1);
	insert(n[10]);
	insert(n[3]);
	insert(n[15]);
	insert(n[1]);
	delete(n[1]);
	printTree(); // all black at this point
	printf("deleting black node\n");
	delete(n[10]); // delete 3 or 15
	printTree();
	return;
}

void deleteSibR(int c) {
	int arr[100];
	Node* n[100];
	for (int i = 0; i < 100; i++)
		n[i] = initNode(arr+i,1);
	insert(n[50]);
	insert(n[30]);
	insert(n[70]);
	insert(n[20]);
	insert(n[40]);
	insert(n[60]);
	insert(n[80]);
	insert(n[90]);
	delete(n[90]);
	insert(n[10]);
	delete(n[10]);
	printTree(); // tree is [b]->[r r]->[b b b b]
	printf("~~delete~~\n");
	if (c == 0) { // red sib is left
		delete(n[60]);
		delete(n[80]);
		delete(n[70]);
	}
	else {
		delete(n[20]);
		delete(n[40]);
		delete(n[30]);
	}
	printTree();
	return;
}

void rotateTest() {
        int arr[100];
        Node* n[100];
        for (int i = 0; i < 100; i++)
                n[i] = initNode(arr+i,1);
	insert(n[4]);
	insert(n[2]);
	insert(n[6]);
	insert(n[1]);
	insert(n[3]);
	insert(n[5]);
	insert(n[7]);
	printTree();
	printf("rotation\n");
	rotateLeft(n[4]);
	printTree();
	return;
}

void rootTest() {
	int r[1];
	Node* n = initNode(r,1);
	insert(n);
	printTree();
	printf("delete root\n");
	delete(n);
	printTree();
}

int main() {
	//insertTest();
	//simpleDelete();
	//deleteNephR(3); // LL-0, RR-1, LR-2, RL-3
	//deleteNephB();
	//rotateTest();
	//deleteSibR(0); // L case
	//deleteSibR(1); // R case
	//rootTest();

	int* addr = malloc(sizeof(int));
	addr = realloc((void*)addr + 1, 1);

	return 0;
}
