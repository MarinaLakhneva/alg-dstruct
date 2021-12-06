#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <stdio.h>
using namespace std;

const char nl = '\n';
int  U, B, K;
int* weights;
int* prices;
int total_sum_of_set;
int total_weight_of_set;

/*
5(U) 5(B) 20(K)
1 2 4 2 3
7 1 3 4 10
*/


int read_ints(const char* file_name) {
    FILE* file = fopen(file_name, "r");

    fscanf(file, "%d %d %d\n", &U, &B, &K);

    weights = (int*)malloc(sizeof(int) * U);
    if (weights == NULL) {
        printf("No memory allocated!");
        return 0;
    }

    prices = (int*)malloc(sizeof(int) * U);
    if (prices == NULL) {
        printf("No memory allocated!");
        return 0;
    }

    for (int i = 0; i < U; i++) {
        fscanf(file, "%d", &weights[i]);
    }
    for (int i = 0; i < U; i++) {
        fscanf(file, "%d", &prices[i]);
    }
    fclose(file);
}

int get_min(int* a) {
    int id = -1;
    int min = 1000000;
    for (int i = 0; i < U; i++)
        if (a[i] < min && a[i] != 0) {
            id = i;
            min = a[i];
        }
    return id;
}

int sum(int  U, int B, int K) {
    total_sum_of_set = 0;
    total_weight_of_set = 0;
    int min_weight = 100000;

    for (int i = 0; i < U; i++) {
        total_sum_of_set += prices[i];
        total_weight_of_set += weights[i];
        if (min_weight > weights[i])
            min_weight = weights[i];
    }

    if ((total_sum_of_set >= K) && total_weight_of_set <= B) {
        FILE* values;

        char name[] = "output.txt";
        values = fopen(name, "w");
        for (int i = 1; i <= U; i++)
            fprintf(values, "%d ", i);

        fclose(values);
    }

    if (min_weight > B || total_sum_of_set < K) {
        char name[] = "output.txt";
        FILE* values = fopen(name, "w");
        fprintf(values, "%d ", 0);

        fclose(values);
    }

    int cur_weight = total_weight_of_set;
    int cur_sum = total_sum_of_set;
    int flag = 1;

    while (flag != -1 && flag != -2) {
        int min_price_id = get_min(prices);
        cur_weight -= weights[min_price_id];
        cur_sum -= prices[min_price_id];
        weights[min_price_id] = 0;
        prices[min_price_id] = 0;

        if (cur_weight - B <= 0) {
            flag = -2;
            if (cur_sum >= K) {
                flag = -1;
            }
        }
    }

    if (flag == -1) {
        char name[] = "output.txt";
        FILE* values = fopen(name, "w");
        for (int i = 0; i < U; i++) {
            if (weights[i] > 0)
                fprintf(values, "%d ", i + 1);
        }
        fclose(values);
        return 0;
    }
    else if (flag == -2) {
        char name[] = "output.txt";
        FILE* values = fopen(name, "w");
        fprintf(values, "%d ", 0);
        fclose(values);
    }
    return 1;
}

int main() {
    read_ints("input.txt");
    sum(U, B, K);
}