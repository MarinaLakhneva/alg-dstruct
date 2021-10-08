#include <iostream>
#include "LaBa.h"

int main() {

	list* a = (list*)malloc(sizeof(list));
	a->value = ("dog");
	a->next = NULL;

	list* b = (list*)malloc(sizeof(list));
	b->value = ("durk");
	b->next = a;

	list* c = (list*)malloc(sizeof(list));
	c->value = ("donkey");
	c->next = b;

	list* d = (list*)malloc(sizeof(list));
	d->value = ("monkey");
	d->next = c;

	list* e = (list*)malloc(sizeof(list));
	e->value = ("cat");
	e->next = d;

    print(e);
    sort(e);

    printf("\n");
    print(e);
    return 0;
}