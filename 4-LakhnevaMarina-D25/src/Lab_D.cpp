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
int* answer;
int number_in_answer = 0;
int* ethalon;

/*
in file
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
    return 1;
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
    int flag = 1;

    for (int i = 0; i < U; i++) {
        total_sum_of_set += prices[i];
        total_weight_of_set += weights[i];
        if (min_weight > weights[i])
            min_weight = weights[i];
    }

    if ((total_sum_of_set >= K) && total_weight_of_set <= B) {

        answer = (int*)malloc(sizeof(int) * (U + 1));
        if (answer == NULL) {
            printf("No memory allocated!");
            return 0;
        }

        for (int i = 1; i <= U; i++)
            answer[i - 1] = i;
        number_in_answer = U;
        return 1;
    }

    else if (min_weight > B || total_sum_of_set < K) {
        return 0;
    }

    int cur_weight = total_weight_of_set;
    int cur_sum = total_sum_of_set;

    while (flag != -1 && flag != -2) {
        int min_price_id = get_min(prices);
        if (min_price_id == -1) return -1;
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
        number_in_answer = 0;

        answer = (int*)malloc(sizeof(int) * U);
        if (answer == NULL) {
            printf("No memory allocated!");
            return 0;
        }

        for (int i = 0; i < U; i++) {
            if (weights[i] > 0) {
                answer[number_in_answer++] = i + 1;
            }
        }
        return 1;
    }
    else if (flag == -2) {
        return 0;
    }
    return 0;
}

void free_globals() {
    free(weights);
    free(prices);
    number_in_answer = 0;
}

int summary(int  U, int B, int K) {
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

int* tests_results;
int number_of_tests;

int test(char input[])
{
    FILE* test;
    if ((test = fopen(input, "r"))) {

        fscanf(test, "%d\n", &number_of_tests);
        if (number_of_tests < 1)
            return -1;

        tests_results = (int*)malloc(sizeof(int) * (number_of_tests));
        int cnt = 0;


        while (cnt < number_of_tests) {

            fscanf(test, "%d %d %d", &U, &B, &K);

            weights = (int*)malloc(sizeof(int) * (U + 1));
            if (weights == NULL) {
                printf("No memory allocated!");
                return 0;
            }

            prices = (int*)malloc(sizeof(int) * (U + 1));
            if (prices == NULL) {
                printf("No memory allocated!");
                return 0;
            }


            for (int i = 0; i < U; i++) {
                fscanf(test, "%d ", &weights[i]);
            }

            for (int i = 0; i < U; i++) {
                fscanf(test, "%d ", &prices[i]);
            }
            tests_results[cnt] = 1;
            if (sum(U, B, K)) {

                ethalon = (int*)malloc(sizeof(int) * (U + 1));
                if (ethalon == NULL) {
                    printf("No memory allocated!");
                    return 0;
                }

                for (int i = 0; i < number_in_answer; i++) {
                    fscanf(test, "%d ", &ethalon[i]);
                    if (ethalon[i] != answer[i]) {
                        tests_results[cnt] = 0;
                        break;
                    }
                }
                free(answer);
                free(ethalon);
            }
            else {
                int checker;
                fscanf(test, "%d\n", &checker);
                if (checker != 0)
                    tests_results[cnt] = 0;
            }
            free_globals();
            cnt++;

        }
        fclose(test);
        return 1;
    }
    fprintf(stderr, "Wrong file name.\n");
    return -1;
}

int main() {
    //char file_name[] = "test_D.txt";
    //if (test(file_name) == 1) {
    //    for (int i = 0; i < number_of_tests; i++) {
    //        if (tests_results[i])
    //            printf("Test number %d is passed successfully\n", i + 1);
    //        else
    //            printf("Test number %d is failed\n", i + 1);
    //    }
    //    free(tests_results);
    //}
    //return 0;

    read_ints("input.txt");
    summary(U, B, K);
}