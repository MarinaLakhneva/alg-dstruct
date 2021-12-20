#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

struct Tree {
	int key;
	int num;
	struct Tree* right;
	struct Tree* left;
	struct Tree* parent;
};

typedef struct Tree Tree;

int append(Tree* tree, int key) {
	Tree* ptr = tree;
	Tree* prevPtr = NULL;

	Tree* cur = (Tree*)malloc(sizeof(Tree));
	if (cur == NULL) {
		printf("No memory allocated!");
		return 0;
	}
	
	if (tree == NULL) {
		fprintf(stderr, "NULL pointer error");
		return -1;
	}

	if (cur == NULL) {
		fprintf(stderr, "Can't allocate memory for new tree element");
		return -2;
	}

	while (ptr != NULL) {
		prevPtr = ptr;
		ptr->num += 1;

		if (key < ptr->key) {
			ptr = ptr->left;
		}
		else {
			ptr = ptr->right;
		}
	}

	if (key < prevPtr->key) {
		prevPtr->left = cur;
	}
	else {
		prevPtr->right = cur;
	}

	cur->key = key;
	cur->num = 1;
	cur->right = NULL;
	cur->left = NULL;
	cur->parent = prevPtr;

	return 1;
}

Tree* K_min(Tree* tree, int k) {
	int leftSize;

	if ((tree->num < k) || (k <= 0)) {
		return NULL;
	}

	if (tree->left != NULL) {
		leftSize = tree->left->num + 1;
	}
	else {
		leftSize = 1;
	}

	if (leftSize != k) {
		if (leftSize > k) {
			if (tree->left != NULL) {
				tree = K_min(tree->left, k);
			}
		}
		else {
			if (tree->right != NULL) {
				tree = K_min(tree->right, k - leftSize);
			}
		}
	}
	return tree;
}

void print(Tree* tree) {
	
	if (tree == NULL){
		return;
	}

	printf("%d ", tree->key);

	if (tree->left != NULL) {
		print(tree->left);
	}

	if (tree->right != NULL) {
		print(tree->right);
	}
}

void print_min_prev_K(Tree* tree) {
	Tree* parent;
	
	if (tree == NULL) {
		return;
	}

	while (tree->parent != NULL) {
		parent = tree->parent;

		if (parent->right == tree) {
			print(parent->left);
			printf("%d ", parent->key);
		}
		else {
			printf("%d ", parent->key);
		}
		tree = parent;
	}
}

void print_min_K(Tree* tree, int k) {
	Tree* kMin = K_min(tree, k);

	if ((kMin->key % 2) == 0) {
		print_min_prev_K(kMin);

	}
	else {
		printf("Element is odd");
	}
}

int main() {
	Tree* tree = (Tree*)malloc(sizeof(Tree));
	if (tree == NULL) {
		printf("No memory allocated!");
		return 0;
	}

	if (tree == NULL) {
		return 0;
	}
	
	tree->left = NULL;
	tree->right = NULL;
	tree->parent = NULL;
	tree->key = 31;
	tree->num = 1;

	append(tree, 29);
	append(tree, 26);
	append(tree, 30);
	append(tree, 33);
	append(tree, 32);
	append(tree, 35);
	append(tree, 34);

	print_min_K(tree, 7);

	return 0;
}