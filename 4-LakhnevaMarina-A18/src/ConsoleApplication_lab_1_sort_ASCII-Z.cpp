#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct list {
    const char* value;
    struct list* next;
} list;

list* create(const char* word) {
    list* tmp = (list*)malloc(sizeof(list));
    if (tmp == NULL) {
        +printf("Требуемая память не выделена!");
    }
    tmp->value = word;
    tmp->next = NULL;
    return(tmp);
}

list* append(const char* word, list* head) {
    list* tmp = (list*)malloc(sizeof(list));
    if (tmp == NULL) {
        +printf("Требуемая память не выделена!");
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
        const char* value1 = fin->value;
        const char* value2 = fin->next->value;

            if (strcmp(value2, value1) < 0) {
                const char* temp = fin->value;
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
//Проверяем значение первого элемента созданного списка
void assert1_creation_of_list_value(void) {
    list* a1 = create("dog");
    assert(a1->value == "dog");
}
//Проверяем, что у единственного первого элемента нет ссылок(нулевая ссылка)
void assert2_creation_of_list_no_next(void) {
    list* a1 = create("dog");
    assert(a1->next == NULL);
}
//Проверяем значение добавляемого элемента
void assert3_check_append_value(void) {
    list* a1 = create("dog");
    list* a2 = append("cat", a1);
    assert(a2->value == "cat");
}
//Проверяем связь между элементами, что в next первого элемента лежит ссылка на следующий
void assert4_check_append_connection(void) {
    list* a1 = create("dog");
    list* a2 = append("cat", a1);
    assert(a2->next == a1);
}
//Проверяем работоспособность сортировки, что зачение первого элемента есть самая "маленькая" буква
void assert5_check_sort(void) {
    list* a1 = create("c");
    list* a2 = append("a", a1);
    list* a3 = append("q", a2);
    sort(a3);
    assert(a3->value == "a");
}
//Проверяем, что сортировка проверяет следующие буквы, если первые совпадают
void assert6_check_sort_order(void) {
    list* a1 = create("ac");
    list* a2 = append("ab", a1);
    list* a3 = append("ak", a2);
    sort(a3);
    assert(a3->value == "ab");
}

const char main() {
    assert1_creation_of_list_value();
    assert2_creation_of_list_no_next();
    assert3_check_append_value();
    assert4_check_append_connection();
    assert5_check_sort();
    assert6_check_sort_order();

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