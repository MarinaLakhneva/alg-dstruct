#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct tree_b {
    struct tree_b* first;
    struct tree_b* second;
    struct tree_b* third;
    struct tree_b* fourth;

    struct tree_b* parent;

    int size;
    int key[3];

} tree_b;

tree_b* create_node(int value) {
    tree_b* nodeToAdd = (tree_b*)malloc(sizeof(tree_b));
    if(nodeToAdd == NULL) {
        printf("No memory allocated!");
        return 0;
    }

    if (nodeToAdd) {
        nodeToAdd->first = NULL;
        nodeToAdd->second = NULL;
        nodeToAdd->third = NULL;
        nodeToAdd->fourth = NULL;

        nodeToAdd->parent = NULL;

        nodeToAdd->size = 1;
        nodeToAdd->key[0] = value;

        return nodeToAdd;
    }
    return NULL;
}

tree_b* create_node_2(int value, tree_b* one, tree_b* two, tree_b* three, tree_b* four, tree_b* parent) {
    tree_b* nodeToAdd = (tree_b*)malloc(sizeof(tree_b));
    if (nodeToAdd == NULL) {
        printf("No memory allocated!");
        return 0;
    }

    if (nodeToAdd) {
        nodeToAdd->first = one;
        nodeToAdd->second = two;
        nodeToAdd->third = three;
        nodeToAdd->fourth = four;

        nodeToAdd->parent = parent;

        nodeToAdd->size = 1;
        nodeToAdd->key[0] = value;

        return nodeToAdd;
    }
    return NULL;
}

char find(int value, int* key, int size) {
    for (int i = 0; i < size; ++i) {
        if (key[i] == value) {
            return 1;
        }
    }
    return 0;
}

void swap(int* x, int* y) {
    int r = (*x);
    (*x) = (*y);
    (*y) = r;
}

void sort(int* x, int* y) {
    if (*x > *y) {
        swap(x, y);
    }
}

void sort_1(int* x, int* y, int* z) {
    if (*x > *y) {
        swap(x, y);
    }

    if (*x > *z) {
        swap(x, z);
    }

    if (*y > *z) {
        swap(y, z);
    }
}

void sort_keys(int size, int* key) {
    if (size == 1) {
        return;
    }

    if (size == 2) {
        sort(&key[0], &key[1]);
    }

    if (size == 3) {
        sort_1(&key[0], &key[1], &key[2]);
    }
}

void add_key(int value, tree_b* treeNode) {
    if (treeNode == NULL) {
        return;
    }

    treeNode->key[treeNode->size] = value;
    treeNode->size++;

    sort_keys(treeNode->size, treeNode->key);
}

void remove_key(int value, tree_b* treeNode) {
    if (treeNode == NULL) {
        return;
    }

    if (treeNode->size >= 1 && treeNode->key[0] == value) {
        treeNode->key[0] = treeNode->key[1];
        treeNode->key[1] = treeNode->key[2];
        treeNode->size--;
    }
    else if (treeNode->size == 2 && treeNode->key[1] == value) {
        treeNode->key[1] = treeNode->key[2];
        treeNode->size--;
    }
}

void become_node_2(int value, int* key, tree_b* treeNode, tree_b* one, tree_b* two) {

    treeNode->first = one;
    treeNode->second = two;
    treeNode->third = NULL;
    treeNode->fourth = NULL;

    treeNode->parent = NULL;

    treeNode->size = 1;
    key[0] = value;
}

char leaf(tree_b* tree) {
    if (tree == NULL) {
        return 0;
    }

    if ((tree->first == NULL) && (tree->second == NULL) && (tree->third == NULL)) {
        return 1;
    }
    return 0;
}

tree_b* split(tree_b* item) {
    if (item == NULL) {
        return NULL;
    }

    if (item->size < 3) {
        return item;
    }
    tree_b* x = create_node_2(item->key[0], item->first, item->second, NULL, NULL, item->parent);
    tree_b* y = create_node_2(item->key[2], item->third, item->fourth, NULL, NULL, item->parent);

    if (x->first) {
        x->first->parent = x;
    }
    if (x->second) {
        x->second->parent = x;
    }
    if (y->first) {
        y->first->parent = y;
    }
    if (y->second) {
        y->second->parent = y;
    }

    if (item->parent != NULL) {
        add_key(item->key[1], item->parent);

        if (item->parent->first == item) {
            item->parent->first = NULL;
        }
        else if (item->parent->second == item) {
            item->parent->second = NULL;
        }
        else if (item->parent->third == item) {
            item->parent->third = NULL;
        }

        if (item->parent->first == NULL) {
            item->parent->fourth = item->parent->third;
            item->parent->third = item->parent->second;
            item->parent->second = y;
            item->parent->first = x;
        }
        else if (item->parent->second == NULL) {
            item->parent->fourth = item->parent->third;
            item->parent->third = y;
            item->parent->second = x;
        }
        else {
            item->parent->fourth = y;
            item->parent->third = x;
        }

        tree_b* tmp = item->parent;

        free(item);
        return tmp;
    }
    else {
        x->parent = item;
        y->parent = item;

        become_node_2(item->key[1], item->key, item, x, y);
        return item;
    }
}

tree_b* search(tree_b* tree, int value) {
    if (tree == NULL) {
        return NULL;
    }

    if (find(value, tree->key, tree->size)) {
        return tree;
    }
    else if (value < tree->key[0]) {
        return search(tree->first, value);
    }
    else if ((tree->size == 2) && (value < tree->key[1]) || (tree->size == 1)) {
        return search(tree->second, value);
    }
    else if (tree->size == 2) {
        return search(tree->third, value);
    }
}

tree_b* add_node(tree_b* tree, int value) {
    if (tree == NULL) {
        return create_node(value);
    }

    if (search(tree, value)) {
        return split(tree);
    }

    if (leaf(tree)) {
        add_key(value, tree);
    }
    else if (value <= tree->key[0]) {
        add_node(tree->first, value);
    }
    else if ((tree->size == 1) || ((tree->size == 2) && value <= tree->key[1])) {
        add_node(tree->second, value);
    }
    else {
        add_node(tree->third, value);
    }
    return split(tree);
}

tree_b* find_min(tree_b* tree) {
    if (tree == NULL) {
        return tree;
    }

    if ((tree->first) == NULL) {
        return tree;
    }
    else {
        return find_min(tree->first);
    }
}

tree_b* redistribute(tree_b* leaf) {
    if (leaf == NULL) {
        return NULL;
    }

    tree_b* parent = leaf->parent;
    tree_b* first = parent->first;
    tree_b* second = parent->second;
    tree_b* third = parent->third;


    if ((parent->size == 2) && (first->size < 2) && (second->size < 2) && (third->size < 2)) {
        if (first == leaf) {
            parent->first = parent->second;
            parent->second = parent->third;
            parent->third = NULL;

            add_key(parent->key[0], parent->first);

            parent->first->third = parent->first->second;
            parent->first->second = parent->first->first;

            if (leaf->first != NULL) {
                parent->first->first = leaf->first;
            }
            else if (leaf->second != NULL) {
                parent->first->first = leaf->second;
            }

            if (parent->first->first != NULL) {
                parent->first->first->parent = parent->first;
            }
            remove_key(parent->key[0], parent);
        }
        else if (second == leaf) {
            add_key(parent->key[0], first);
            remove_key(parent->key[0], parent);

            if (leaf->first != NULL) {
                first->third = leaf->first;
            }
            else if (leaf->second != NULL) {
                first->third = leaf->second;
            }

            if (first->third != NULL) {
                first->third->parent = first;
            }

            parent->second = parent->third;
            parent->third = NULL;

            free(second);
        }
        else if (third == leaf) {
            add_key(parent->key[1], second);

            parent->third = NULL;

            remove_key(parent->key[1], parent);

            if (leaf->first != NULL) {
                second->third = leaf->first;
            }
            else if (leaf->second != NULL) {
                second->third = leaf->second;
            }

            if (second->third != NULL) {
                second->third->parent = second;
            }
            free(third);
        }
    }
    else if ((parent->size == 2) && ((first->size == 2) || (second->size == 2) || (third->size == 2))) {
        if (third == leaf) {
            if (leaf->first != NULL) {
                leaf->second = leaf->first;
                leaf->first = NULL;
            }

            add_key(parent->key[1], leaf);
            if (second->size == 2) {
                parent->key[1] = second->key[1];

                remove_key(second->key[1], second);

                leaf->first = second->third;
                second->third = NULL;

                if (leaf->first != NULL) {
                    leaf->first->parent = leaf;
                }

            }
            else if (first->size == 2) {
                parent->key[1] = second->key[0];
                leaf->first = second->second;
                second->second = second->first;

                if (leaf->first != NULL) {
                    leaf->first->parent = leaf;
                }

                second->key[0] = parent->key[0];
                parent->key[0] = first->key[1];

                remove_key(first->key[1], first);

                second->first = first->third;
                if (second->first != NULL) {
                    second->first->parent = second;
                }
                first->third = NULL;
            }
        }
        else if (second == leaf) {
            if (third->size == 2) {
                if (leaf->first == NULL) {
                    leaf->first = leaf->second;
                    leaf->second = NULL;
                }

                add_key(parent->key[1], second);

                parent->key[1] = third->key[0];

                remove_key(third->key[0], third);

                second->second = third->first;

                if (second->second != NULL) {
                    second->second->parent = second;
                }
                third->first = third->second;
                third->second = third->third;
                third->third = NULL;
            }
            else if (first->size == 2) {
                if (leaf->second == NULL) {
                    leaf->second = leaf->first;
                    leaf->first = NULL;
                }
                add_key(parent->key[0], second);

                parent->key[0] = first->key[1];

                remove_key(first->key[1], first);

                second->first = first->third;

                if (second->first != NULL) {
                    second->first->parent = second;
                }
                first->third = NULL;
            }
        }
        else if (first == leaf) {
            if (leaf->first == NULL) {
                leaf->first = leaf->second;
                leaf->second = NULL;
            }

            add_key(parent->key[0], first);

            if (second->size == 2) {
                parent->key[0] = second->key[0];

                remove_key(second->key[0], second);

                first->second = second->first;

                if (first->second != NULL) {
                    first->second->parent = first;
                }
                second->first = second->second;
                second->second = second->third;
                second->third = NULL;
            }
            else if (third->size == 2) {
                parent->key[0] = second->key[0];
                second->key[0] = parent->key[1];
                parent->key[1] = third->key[0];

                remove_key(third->key[0], third);

                first->second = second->first;

                if (first->second != NULL) {
                    first->second->parent = first;
                }
                second->first = second->second;
                second->second = third->first;

                if (second->second != NULL) {
                    second->second->parent = second;
                }
                third->first = third->second;
                third->second = third->third;
                third->third = NULL;
            }
        }
    }
    else if (parent->size == 1) {
    add_key(parent->key[0], leaf);

        if (first == leaf && second->size == 2) {
            parent->key[0] = second->key[0];

            remove_key(second->key[0], second);

            if (leaf->first == NULL) {
                leaf->first = leaf->second;
            }
            leaf->second = second->first;
            second->first = second->second;
            second->second = second->third;
            second->third = NULL;

            if (leaf->second != NULL) {
                leaf->second->parent = leaf;
            }
        }
        else if (second == leaf && first->size == 2) {
            parent->key[0] = first->key[1];

            remove_key(first->key[1], first);

            if (leaf->second == NULL) {
                leaf->second = leaf->first;
            }
            leaf->first = first->third;
            first->third = NULL;

            if (leaf->first != NULL) {
                leaf->first->parent = leaf;
            }
        }
    }
    return parent;
}

tree_b* merge(tree_b* leaf) {
    if (leaf == NULL) {
        return NULL;
    }
    tree_b* parent = leaf->parent;

    if (parent->first == leaf) {
        add_key(parent->key[0], parent->second);

        parent->second->third = parent->second->second;
        parent->second->second = parent->second->first;

        if (leaf->first != NULL) {
            parent->second->first = leaf->first;
        }
        else if (leaf->second != NULL) {
            parent->second->first = leaf->second;
        }

        if (parent->second->first != NULL) {
            parent->second->first->parent = parent->second;
        }
        remove_key(parent->key[0], parent);
        free(parent->first);

        parent->first = NULL;
    }
    else if (parent->second == leaf) {
        add_key(parent->key[0], parent->first);

        if (leaf->first != NULL) {
            parent->first->third = leaf->first;
        }
        else if (leaf->second != NULL) {
            parent->first->third = leaf->second;
        }

        if (parent->first->third != NULL) {
            parent->first->third->parent = parent->first;
        }

        remove_key(parent->key[0], parent);
        free(parent->second);

        parent->second = NULL;
    }
    if (parent->parent == NULL) {
        tree_b* tmp = NULL;

        if (parent->first != NULL) {
            tmp = parent->first;
        }
        else {
            tmp = parent->second;
        }

        tmp->parent = NULL;

        free(parent);
        return tmp;
    }
    return parent;
}

tree_b* fix(tree_b* leaf) {
    if (leaf == NULL) {
        return NULL;
    }

    if (leaf->size == 0 && leaf->parent == NULL) {
        free(leaf);
        return NULL;
    }

    if (leaf->size != 0) {
        if (leaf->parent) {
            return fix(leaf->parent);
        }
        else {
            return leaf;
        }
    }

    tree_b* parent = leaf->parent;

    if (parent->first->size == 2 || parent->second->size == 2 || parent->size == 2) {
        leaf = redistribute(leaf);
    }
    else if (parent->size == 2 && parent->third->size == 2) {
        leaf = redistribute(leaf);
    }
    else {
        leaf = merge(leaf);
    }
    return fix(leaf);
}

tree_b* remove_node(tree_b* tree, int value) {
    if (tree == NULL) {
        return NULL;
    }

    tree_b* item = search(tree, value);

    if (item == NULL) {
        return tree;
    }

    tree_b* min = NULL;
    if (item->key[0] == value) {
        min = find_min(item->second);
    }
    else {
        min = find_min(item->third);
    }

    if (min != NULL) {
        int* z = (value == item->key[0] ? &(item->key[0]) : &(item->key[1]));
        swap(z, &min->key[0]);
        item = min;
    }
    remove_key(value, item);
    return fix(item);
}

void print(tree_b* tree) {
    if (tree == NULL) {
        return;
    }
    print(tree->first);

    for (int i = 0; i < tree->size; i++) {
        printf("%d ", tree->key[i]);
    }
    print(tree->second);
    print(tree->third);
}

void destroy(tree_b* tree) {
    if (tree == NULL) {
        return;
    }
    destroy(tree->first);
    destroy(tree->second);
    destroy(tree->third);
    free(tree);
}

int main(void) {
    char command;
    int key = 0;

    tree_b* tree = NULL;

    while (scanf("%c", &command) >= 1) {
        if (command != 'p' && command != 'q') {
            scanf("%i", &key);
        }

        switch (command) {
        case 'a':
            tree = add_node(tree, key);
            break;
        case 'r':
            tree = remove_node(tree, key);
            break;
        case 'f':
            if (search(tree, key)) {
                puts("yes");
            }
            else {
                puts("no");
            }
            break;

        case 'p':
            print(tree);
            putchar('\n');
            break;

        case 'q':
            destroy(tree);
            return 0;
        }
    }
}