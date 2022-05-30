#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/* 아래 구조체 제외하고 전역변수 사용 금지
전역변수 사용 시 0점 처리 */
typedef struct threadedTree* threadedPointer;
typedef struct threadedTree {
	char data;
	short int leftThread, rightThread;
	threadedPointer leftChild, rightChild;
} threadedTree;

/* 구현할 함수들
함수의 반환형이나 parameter는 수정 가능하지만, 함수명은 변경 불가
함수명 변경 시 해당 함수 미구현으로 간주하고 점수 미부여 */
threadedPointer initTree(FILE* fp); // 직접 구현
threadedPointer insucc(threadedPointer tree); // 교재 확인
threadedPointer inpredec(threadedPointer tree); // 직접 구현
void insertRight(threadedPointer parent, threadedPointer child, char data); // 교재 확인
void insertLeft(threadedPointer parent, threadedPointer child, char data); // 직접 구현
threadedPointer tinorderSearch(threadedPointer tree, char data); // 직접 구현
void tinorder(threadedPointer tree); // 교재 확인
void tpreorder(threadedPointer tree); // 직접 구현

void main() {
	/* main 함수는 수정할 수 없음
	main 함수 수정 시 0점 처리 */
	FILE* fp = fopen("input.txt", "r");
	threadedPointer my_tree = initTree(fp);

	tinorder(my_tree);
	printf("\n");
	tpreorder(my_tree->leftChild);
	printf("\n");

	fclose(fp);
	return;
}

threadedPointer initTree(FILE* fp) {
	threadedPointer root, newnode, temp;
	char operation, data, direction;

	root = (threadedPointer)malloc(sizeof(threadedTree));
	root->leftThread = true;
	root->rightThread = false;
	root->leftChild = root;
	root->rightChild = root;

	while (1) {
		int res = fscanf(fp, "%c", &operation);
		if (res == EOF) break;
		if (operation == 'I') {
			fscanf(fp, "%c %c", &data, &direction);
			newnode = (threadedPointer)malloc(sizeof(threadedTree));
			if (root->leftThread == true) {
				if (direction == 'L') {
					insertLeft(root, newnode, data);
				}
				else {
					insertRight(root, newnode, data);
				}
				root->leftThread = false;
			}
			else {
				if (direction == 'L') {
					insertLeft(temp, newnode, data);
				}
				else {
					insertRight(temp, newnode, data);
				}
			}
		}
		else {
			fscanf(fp, "%c", &data);
			temp = tinorderSearch(root, data);
		}
	}
	return root;
}

threadedPointer insucc(threadedPointer tree) {
	threadedPointer temp;
	temp = tree->rightChild;
	if (!tree->rightThread) {
		while (!temp->leftThread) {
			temp = temp->leftChild;
		}
	}
	retrun temp;
}

threadedPointer inpredec(threadedPointer tree) {
	threadedPointer temp;
	temp = tree->leftChild;
	if (!tree->leftThread) {
		while (!temp->rightThread) {
			temp = temp->rightChild;
		}
	}
	retrun temp;
}

void insertRight(threadedPointer parent, threadedPointer child, char data) {
	child->data = data;
	child->rightChild = parent->rightChild;
	child->rightThread = parent->rightThread;
	child->leftChild = parent;
	child->leftThread = true;

	parent->rightChild = child;
	parent->rightThread = false;
	if (!child->rightThread) {
		temp = insucc(child);
		temp->leftChild = child;
	}
}

void insertLeft(threadedPointer parent, threadedPointer child, char data) {
	child->data = data;
	child->leftChild = parent->leftChild;
	child->leftThread = parent->leftThread;
	child->rightChild = parent;
	child->rightThread = true;

	parent->leftChild = child;
	parent->leftThread = false;
	if (!child->leftThread) {
		temp = inpredec(child);
		temp->rightChild = child;
	}
}

threadedPointer tinorderSearch(threadedPointer tree, char data) {
	threadedPointer temp = tree;
	for (;;) {
		temp = insucc(temp);
		if (temp->data == data) break;
	}
	return temp;
}

void tinorder(threadedPointer tree); {
	threadedPointer temp = tree;
	for (;;) {
		temp = insucc(temp);
		if (temp == tree) break;
		printf("%3c", temp->data);
	}
}

void tpreorder(threadedPointer tree) {
	threadedPointer temp = tree;
	for (;;) {
		temp = inpredec(temp);
		if (temp == tree) break;
		printf("%3c", temp->data);
	}
}