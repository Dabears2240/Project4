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

void deleteSibB() {
	// change target for different cases
	// case LL:	18, 15
	// case RR:	 1,  5
	// case LR:	30, 25
	// case RL:	60, 70
	int target1 = 0;
	int target2 = 0;
	
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
	return;
}

int main() {

	simpleDelete();

	return 0;
}
