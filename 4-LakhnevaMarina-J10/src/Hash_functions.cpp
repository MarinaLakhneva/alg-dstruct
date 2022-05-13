# define _CRT_SECURE_NO_WARNINGS
#include<inttypes.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include <time.h>

#define BYTE 256
uint16_t  CRC_TABLE[BYTE];
#define WIDTH  (8 * sizeof(uint16_t))
#define TOPBIT (1 << (WIDTH - 1))

#define POLYNOMIAL (0x1021)

#define TABLE_SIZE 101
int COLISSION_TABLE[TABLE_SIZE] = { 0 };



typedef struct List_t {
    struct List_t* next;
    char* data;
}List_t;
List_t* HASH_TABLE[TABLE_SIZE];

static void Add_list(List_t* parent, char* message) {
    int len = strlen(message) + 1;

    List_t* current = parent;
    for (; current->next != NULL; current = current->next) { //!
        if (strcmp(current->next->data, message) == 0) {
            return;
        }
    }

    List_t* new_list = (List_t*)malloc(sizeof(List_t));
    if (new_list == NULL) {
        printf("No memory allocated!");
        return;
    }

    new_list->next = NULL;
    new_list->data = (char*)calloc(len, sizeof(char));
    if (new_list->data == NULL) {
        printf("The problem with the pointer to the allocated memory!");
        return;
    }
    strcpy(new_list->data, message);
    current->next = new_list;
}

static int Find_list(List_t* parent, char* message) {
    for (List_t* current = parent->next; current != NULL; current = current->next) {
        if (strcmp(current->data, message) == 0) {
            return 1;
        }
    }
    return 0;
}

static void Delete_list(List_t* parent, char* message) {
    List_t* previous = parent;
    for (List_t* current = parent->next; current != NULL; current = current->next) {
        if (strcmp(current->data, message) == 0) {
            previous->next = current->next;

            free(current->data);
            free(current);
            return;
        }
        previous = current;
    }
}

void Create_CRC_table() {
    uint16_t  remainder;
    for (int dividend = 0; dividend < BYTE; dividend++) {
        remainder = dividend << (WIDTH - 8);

        for (uint8_t bit = 8; bit > 0; bit--) {
            if (remainder & TOPBIT) {
                remainder = (remainder << 1) ^ POLYNOMIAL;
            }
            else {
                remainder = (remainder << 1);
            }
        }
        CRC_TABLE[dividend] = remainder;
    }
}

uint16_t CRC(char* message) {
    int len = strlen(message) + 1;

    uint8_t data;
    uint16_t remainder = 0;

    for (int i = 0; i < len; i++) {
        data = message[i] ^ (remainder >> (WIDTH - 8));
        remainder = CRC_TABLE[data] ^ (remainder << 8);
    }
    return remainder;
}

void Add_hash_table(char* message) {
    unsigned index = CRC(message) % TABLE_SIZE;

    if (HASH_TABLE[index] == NULL) {
        HASH_TABLE[index] = (List_t*)malloc(sizeof(List_t));
        if (HASH_TABLE[index] == NULL) {
            printf("No memory allocated!");
            return;
        }
        HASH_TABLE[index]->next = NULL;
    }
    COLISSION_TABLE[index]++;

    Add_list(HASH_TABLE[index], message);
}

int Find_hash_table(char* message) {
    unsigned index = CRC(message) % TABLE_SIZE;

    if (HASH_TABLE[index] == NULL) {
        return 0;
    }
    return Find_list(HASH_TABLE[index], message);
}

void Delete_hash_table(char* message) {
    unsigned index = CRC(message) % TABLE_SIZE;

    if (HASH_TABLE[index] == NULL) {
        return;
    }
    Delete_list(HASH_TABLE[index], message);
}

void Collision(char* message) {
    unsigned a = CRC(message);
    int i = 2;
    char c[10000];
    
    if (a == CRC(c)) {
            puts(c);
            return;
    }
}

void Test_niformity() {
    srand(time(NULL));

    char* str = (char*)calloc(101, sizeof(char));
    if (str == NULL) {
        printf("The problem with the pointer to the allocated memory!");
        return;
    }

    for (int i = 0; i < TABLE_SIZE; i++) {
        for (int i = 0; i < 101; i++) {
            str[i] = '\0';
        }
        int words_num = rand() % 100;
        for (int k = 0; k < words_num; k++) {
            str[k] = (char)(rand() % 256);
        }
        Add_hash_table(str);
    }

    for (int i = 1; i < TABLE_SIZE + 1; i++) {
        printf("%i  ", COLISSION_TABLE[i - 1]);
        if (i % 25 == 0) {
            puts("");
        }
    }

    int collision_number[15] = { 0 };
    for (int i = 0; i < TABLE_SIZE; i++) {
        collision_number[COLISSION_TABLE[i]]++;
    }

    puts("");
    int flag = 0;

    for (int i = 14; i >= 0; i--) {
        if (collision_number[i] != 0) {
            flag = 1;
        }
        if (flag) {
            if (collision_number[i] != -1) {
                printf("Number of cells with %i elements: %i \n", i, collision_number[i]);
            }
        }
    }
}

int main() {
    Create_CRC_table();
    
    char command;
    char message[1000];

    while (scanf("%c", &command) >= 1) {

        switch (command) {
        case 'a':
            scanf("%s", message);
            Add_hash_table(message);
            break;
        case 'r':
            scanf("%s", message);
            Delete_hash_table(message);
            break;
        case 'f':
            scanf("%s", message);
            if (Find_hash_table(message))
                puts("yes");
            else
                puts("no");
            break;
        case 'q':
            return 0;
            break;
        }
    }
    return 0;
}