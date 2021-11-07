#include <iostream>
#include <stdlib.h>
#include <inttypes.h>

#ifndef __MEMALLOCATOR_H__E71A34CB
#define __MEMALLOCATOR_H__E71A34CB

#ifdef __cplusplus
extern "C" {
#endif

    struct Node {
        Node* next_node;
        Node* prev_node;
        int is_free;
        int size;
    };

    Node* first_node = NULL; //глобальный указатель  
    int mem_size = 0;

    // Инициализировать систему памяти с помощью блока памяти pMemory.
    int meminit(void* pMemory, int size) { // size - размер всей память 
        if (first_node != NULL)
            return -1;
        if (size <= sizeof(Node))
            return -1;
        if (pMemory == NULL) //pMemory - указатель на память
            return -1;

        first_node = (Node*)pMemory;
        first_node->next_node = NULL;
        first_node->prev_node = NULL;
        first_node->is_free = true;
        first_node->size = size - sizeof(Node);
        mem_size = size;
        return 0;
    }

    // Выделяем блок памяти размером 'size'.
    // Возвращает указатель на блок памяти, если он успешен, иначе 0

    Node* get_first_fit(int size) { // size - размер запрашиваемой памяти  
        Node* current_node = first_node;

        while (current_node != NULL) {
            if (current_node->size >= size && current_node->is_free == 1)
                return current_node;
            current_node = current_node->next_node;
        }
        return NULL;
    }

    void* memalloc(int size) { // size - размер запрашиваемой памяти  
        if (first_node == NULL) // проверяем, чтобы глобальный указатель не был пустой 
            return NULL;

        Node* current_node = get_first_fit(size);
        if (current_node == NULL)
            return(NULL);

        if (current_node->size > sizeof(Node) + size) {
            Node* new_node = (Node*)((char*)current_node + sizeof(Node) + size); // создаем указатель на новый блок
            new_node->size = current_node->size - size - sizeof(Node); // остаток память 
            new_node->next_node = current_node->next_node;

            if (new_node->next_node != NULL) {
                new_node->next_node->prev_node = new_node;
            }
            new_node->prev_node = current_node;
            current_node->next_node = new_node;
            new_node->is_free = 1; // пустой 
            current_node->size = size; // записываем память, которая могла оказаться чуть больше запрашиваемой 
        }
        current_node->is_free = 0; // занят 

        return((char*)current_node + sizeof(Node)); // возвращаем указатель на занятый блок
    }


    // Освободить память, ранее выделенную memalloc
    void  memfree(void* p) {
        Node* current_node = (Node*)((char*)p - sizeof(Node));
        Node* node_for_merge; // создаем указатель, чтобы не трогать current_node, потому как с ним проводим две операци

        if (current_node == NULL)
            return;
        if (current_node->is_free != 0)
            return;
        current_node->is_free = true;

        if (current_node->next_node != NULL) {
            if (current_node->next_node->is_free == 1) {
                node_for_merge = current_node; //работаем с текущим
                node_for_merge->size = node_for_merge->size + sizeof(Node) + node_for_merge->next_node->size;
                if (node_for_merge->next_node->next_node != NULL) {
                    node_for_merge->next_node->next_node->prev_node = node_for_merge;
                    node_for_merge->next_node = node_for_merge->next_node->next_node;
                }
                else {
                    node_for_merge->next_node = NULL;
                }
            }
        }

        if (current_node->prev_node != NULL) {
            if (current_node->prev_node->is_free == 1) {
                node_for_merge = current_node->prev_node; //работаем с предыдущим
                node_for_merge->size = node_for_merge->size + sizeof(Node) + node_for_merge->next_node->size;
                if (node_for_merge->next_node->next_node != NULL) {
                    node_for_merge->next_node->next_node->prev_node = node_for_merge;
                    node_for_merge->next_node = node_for_merge->next_node->next_node;
                }
                else {
                    node_for_merge->next_node = NULL;
                }
            }
        }
    }

    // Здесь вы можете реализовать проверку на утечку памяти
    void  memdone() {
        Node* current_node = first_node;
        int general_size = 0;

        while (current_node != NULL) {
            general_size += current_node->size + sizeof(Node); // a += b <-> a = a + b
            current_node = current_node->next_node;
        }
        if (general_size != mem_size) {
            fprintf(stderr, "Memory leak"); // вывод в поток ошибки 
        }
        first_node = NULL;
        mem_size = 0;
    }

    int  memgetminimumsize() {
        return(sizeof(Node));
    }

    int  memgetblocksize() {
        return(sizeof(Node));
    }

# ifdef __cplusplus
}
# endif
# endif