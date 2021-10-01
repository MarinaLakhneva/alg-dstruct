#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct list {
    char* value;
    struct list* next;
} list;

list* create(char* word) {
    list* tmp = (list*)malloc(sizeof(list));
    if (tmp == NULL) {
        +printf("No memory allocated!"); 
    }
            tmp->value = word;
            tmp->next = NULL;
            return(tmp);
}

list* append(char* word, list* head) {
    list* tmp = (list*)malloc(sizeof(list));
    if (tmp == NULL) {
        +printf("No memory allocated!");
    }
            tmp->value = word;
            tmp->next = head;
            return(tmp);
}

void print(list* fin) {
    while (fin != NULL) {
        printf("%s", fin->value);
        printf("\n");
        fin = fin->next;
    }
}

void sort(list* fin) {
    int swap_counter = 0;
    list* finish = fin;

    while (fin->next != NULL) {
        char* value1 = fin->value;
        char* value2 = fin->next->value;

        if (strcmp(value2, value1) < 0) {
            char* temp = fin->value;
            fin->value = fin->next->value;
            fin->next->value = temp;
            swap_counter = swap_counter + 1;
        }

        if ((fin->next->next == NULL) && (swap_counter != 0)) {
            fin = finish;
            swap_counter = 0;
        }
        else {
            fin = fin->next;
        }
    }
}