#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int vert1;
    int vert2;
    struct node* next;
} node;

node* head_node(int vert1, int vert2) { // создаем голову
    node* new_node = (node*)malloc(sizeof(node));
    
    if (new_node == NULL) {
        printf("No memory allocated!");
        return 0;
    }
    
    new_node->next = NULL;
    new_node->vert1 = vert1;
    new_node->vert2 = vert2;

    return new_node;
}

int add_node(int vert1, int vert2, node* first_node) { // добиваем список 
    node* new_node = (node*)malloc(sizeof(node));
    
    if (new_node == NULL) {
        printf("No memory allocated!");
        return 0;
    }

    node* next = first_node->next;

    new_node->vert1 = vert1;
    new_node->vert2 = vert2;

    first_node->next = new_node;
    new_node->next = next;
}

int get_vert_min(node* main, int start_vert, int* visited) { // поиск самого маленького
    int min = 30000;

    node* current_node = main;

    while (current_node != NULL) {
        if (current_node->vert1 == start_vert) {
            if (visited[current_node->vert2] == 0 && current_node->vert2 < min) {
                min = current_node->vert2;
            }
        }
        else 
            if (current_node->vert2 == start_vert) {
                if (visited[current_node->vert1] == 0 && current_node->vert1 < min) {
                min = current_node->vert1;
                }
            }
            current_node = current_node->next;
    }
    return (min == 30000) ? -1 : min; // (true) ? возвращаем -1, если нет, то min
}

int free_connected_verts(node* main, int start_vert, int* visited) { // функция, считающая кол-во соседей 
    node* current_node = main;
    int counter = 0;

    while (current_node != NULL) {
        if (current_node->vert1 == start_vert) {
            if (visited[current_node->vert2] == 0) {
                counter++;
            }
        }
        else if (current_node->vert2 == start_vert) {
            if (visited[current_node->vert1] == 0) {
                counter++;
            }
        }
        current_node = current_node->next;
    }
    return counter;
}

void dfs(int start_vert, node* first_node, int* visited) {

    if (start_vert < 0)
        return;
    visited[start_vert] = 1;

    //printf(" %d", start_vert);
    int free_verts = free_connected_verts(first_node, start_vert, visited);

    while (free_verts--) {
        int next_vert = get_vert_min(first_node, start_vert, visited);

        dfs(next_vert, first_node, visited);
    }
}

double stress_test__time(int num_verts) {
    int* visited = (int*)malloc(num_verts * sizeof(int));
    
    if (visited == NULL) {
        printf("No memory allocated!");
        return 0;
    }

    node* first_node = head_node(0, 0);

    for (int i = 0; i < num_verts; i++) {
        for (int j = 0; j < num_verts; j++) {
            add_node(i, j, first_node);
        }
    }
    unsigned long time_start = clock();

    dfs(0, first_node, visited);

    double total_time = (double)(clock() - time_start) / CLOCKS_PER_SEC;
    printf("%f", total_time);

    return total_time;
}

int main() {
  
    int size_of_graph;
    scanf("%d\n", &size_of_graph);
    
    int* visited = (int*)malloc(size_of_graph * sizeof(int));
    
    if (visited == NULL) {
        printf("No memory allocated!");
        return 0;
    }

    int vert1, vert2;
    scanf("%d %d", &vert1, &vert2);
    node* first_node = head_node(vert1, vert2);

    char buffer[100];
    bool n = false; // не дает завершить цикл на первой итерации 
    while (1) {

        gets_s(buffer); // функция копирует строчку из console  
        sscanf(buffer, "%d %d", &vert1, &vert2);

        if ((strcmp(buffer, "") == 0) && (n)) { // strcmp - сравнивает значения 
            break;
        }
        add_node(vert1, vert2, first_node);
        n = true;
    }

    for (int i = 0; i < size_of_graph; i++) visited[i] = 0;
    dfs(0, first_node, visited);

    //stress_test__time(2000);    //total_time = 231 sec 
    return 0;
}