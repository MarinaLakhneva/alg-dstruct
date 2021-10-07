#include <iostream>
#include "lab_1.h"

int main() {

    list* a1 = create("dog");
    if (a1 == NULL) {
        return (1);
    }
    list* a2 = append("cat", a1);
    if (a2 == NULL) {
        return (2);
    }
    list* a3 = append("lamb", a2);
    if (a3 == NULL) {
        return(3);
    }
    list* a4 = append("parrot", a3);
    if (a4 == NULL) {
        return (4);
    }
    list* a5 = append("hamster", a4);
    if (a5 == NULL) {
        return (5);
    }
    list* a6 = append("rat", a5);
    if (a6 == NULL) {
        return (6);
    }
    list* a7 = append("pig", a6);
    if (a7 == NULL) {
        return (7);
    }

    print(a7);
    sort(a7);

    printf("\n");
    print(a7);
    return 0;
}