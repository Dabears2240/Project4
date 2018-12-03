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

void deleteNephR() {
	// change target for different cases
	// case LL:	45, 40
	// case RR:	15, 20
	// case LR:	75, 80
	// case RL:	65, 60
	int target1 = 75;
	int target2 = 80;
	
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

int main() {
	//insertTest();
	//simpleDelete();
	//deleteNephR();
	deleteNephB();
	//rotateTest();

	return 0;
}
