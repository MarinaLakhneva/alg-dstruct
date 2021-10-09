#include <iostream>
#include "LaBa.h"

int main() {

	list list_e = { "dog", NULL };
	list list_d = { "durk", &list_e };
	list list_c = { "donkey", &list_d };
	list list_b = { "monkey", &list_c };
	list list_a = { "cat", &list_b };
    print(&list_a);
    sort(&list_a);

    printf("----\n");
    print(&list_a);
    return 0;
}