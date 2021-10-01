#include <iostream>
#include "lab_1.h"

int main() {

    list* a1 = create("dog");
    list* a2 = append("cat", a1);
    list* a3 = append("lamb", a2);
    list* a4 = append("parrot", a3);
    list* a5 = append("hamster", a4);
    list* a6 = append("rat", a5);
    list* a7 = append("pig", a6);

    print(a7);
    sort(a7);

    printf("\n");
    print(a7);
    return 0;
}