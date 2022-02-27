#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Treap {
	int key;
	int value;
	struct Treap* left;
	struct Treap* right;
} Treap;

typedef struct PairTreap {
	struct Treap* right;
	struct Treap* left;
} PairTreap;

Treap* Find(Treap* tree, int key) { // функция поиска
	if (tree == NULL) {
		return NULL;
	}

	if (tree->key == key) {
		return tree;
	}

	if (tree->key > key) {
		Treap* newTree = Find(tree->left, key);
		return newTree;
	}
	else {
		Treap* newTree = Find(tree->right, key);
		return newTree;
	}
}

Treap* Merge(Treap* tree1, Treap* tree2) { // функция слияния
	if (tree1 == NULL) {
		return tree2;
	}
	if (tree2 == NULL) {
		return tree1;
	}

	if (tree1->value > tree2->value) {
		tree1->right = Merge(tree1->right, tree2);
		return tree1;
	}
	else {
		tree2->left = Merge(tree1, tree2->left);
		return tree2;
	}
}

PairTreap Split(Treap* tree, int key) { // функция расщепления
	if (tree == NULL) {
		PairTreap nullTreap = { NULL, NULL };
		return nullTreap;
	}
	else if (key > tree->key) {
		PairTreap tmpPair = Split(tree->right, key);
		tree->right = tmpPair.right;
		PairTreap newTreap = { tree, tmpPair.left };
		return newTreap;
	}
	else {
		PairTreap tmpPair = Split(tree->left, key);
		tree->left = tmpPair.left;
		PairTreap newTreap = { tmpPair.right, tree };
		return newTreap;
	}
}

Treap* Insert(Treap* tree, int key, int value) { // функция добавления
	if (Find(tree, key) != NULL) {
		return tree;
	}

	Treap* newTree = (Treap*)malloc(sizeof(Treap));
	if (newTree == NULL) {
		printf("No memory allocated!");
		return 0;
	}

	if (newTree == NULL) {
		return tree;
	}

	newTree->key = key;
	newTree->value = value;
	newTree->right = NULL;
	newTree->left = NULL;

	PairTreap newPair = Split(tree, key);
	newPair.right = Merge(newPair.right, newTree);

	return Merge(newPair.right, newPair.left);
}

Treap* Delete(Treap* tree, int key) {
	if (Find(tree, key) == NULL)
		return tree;

	PairTreap newPair = Split(tree, key);
	PairTreap newTree = Split(newPair.left, key + 1);

	free(newTree.right);

	return Merge(newPair.right, newTree.left);
}

void Vacant(Treap* tree) {
	if (tree != NULL) {
		Vacant(tree->left);
		Vacant(tree->right);
		free(tree);
	}
	return;
}

int main(void) {
	char command;
	int value;

	Treap* tree = NULL;

		while (fscanf(stdin, "%c %i", &command, &value) > 0) {
			switch (command) {
			case 'a':
				tree = Insert(tree, value, rand());
				break;
			case 'r':
				tree = Delete(tree, value);
				break;
			case 'f':
				if (Find(tree, value))
					printf("yes\n");
				else
					printf("no\n");
				break;
			}
		}
	Vacant(tree);
	return 0;
}
