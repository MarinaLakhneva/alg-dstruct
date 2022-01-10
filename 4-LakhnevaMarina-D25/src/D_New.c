#include <stdio.h>
#include <stdlib.h>

int  U, B, K;
int* weights;
int* prices;
int* answer1;
int* answer;
int best_price = 0;
int number_in_answer = 0;



int read_ints(const char* file_name) {
    FILE* file = fopen(file_name, "r");

    fscanf(file, "%d %d %d\n", &U, &B, &K);

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

    for (int i = 1; i <= U; i++) {
        fscanf(file, "%d", &weights[i]);
    }
    for (int i = 1; i <= U; i++) {
        fscanf(file, "%d", &prices[i]);
    }
    fclose(file);
    return 1;
}



void sum2(int i, int current_weight, int current_price, int cur_quantity, int* answer1)
{
    if(current_weight > B) return;
    if(current_price >= K && current_weight <= B)
    {
        best_price = current_price;
        number_in_answer = cur_quantity;
        for(int i = 1; i <= U; i++) answer[i] = answer1[i];
    }
    if(i > U) return;
    answer1[i] = 1;
    sum2(i+ 1, current_weight + weights[i], current_price + prices[i], cur_quantity + 1, answer1);
    answer1[i] = 0;
    sum2(i+ 1, current_weight, current_price, cur_quantity, answer1);

}

void free_globals() {
    free(weights);
    free(prices);
    number_in_answer = 0;
    best_price = 0;
}


int main() {
    char file_name[] = "test_D.txt";
    FILE* file = fopen(file_name, "r");
    int number_of_tests, cnt = 0;
    fscanf(file, "%d\n", &number_of_tests);
    while(cnt < number_of_tests)
    {
    fscanf(file, "%d %d %d\n", &U, &B, &K);
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

    for (int i = 1; i <= U; i++) {
        fscanf(file, "%d", &weights[i]);
    }
    for (int i = 1; i <= U; i++) {
        fscanf(file, "%d", &prices[i]);
    }
    answer = (int*)malloc(sizeof(int) * (U + 1));
    answer1 = (int*)malloc(sizeof(int) * (U + 1));
    int * res = (int*)malloc(sizeof(int) * (U + 1));
    int * correct_answer = (int*)malloc(sizeof(int) * (U + 1));
    if(!answer || !answer1 || !res || !correct_answer)
        return -1;
    int j = 0;
    sum2(1, 0, 0, 0, answer1);
    if(best_price >= K)
     for(int i = 1; i <= U; i++)
        if(answer[i] == 1)
        {
            res[j] = i;
            j++;
        }
    if(j == 0)
    {
        int is_zero;
        fscanf(file,"%d ", &is_zero);
    }
    int flag = 1;
    for(int i = 0; i < number_in_answer; i++)
    {
        fscanf(file,"%d ", &correct_answer[i]);
        if(correct_answer[i] != res[i])
        {
            printf("Test number %d is falied\n", cnt + 1);
            flag = 0;
            break;
        }
    }
    if(flag)
        printf("Test number %d is passed\n", cnt + 1);
    cnt++;
    free_globals();
    free(answer);
    free(answer1);
    free(correct_answer);
    free(res);
    }

    return 0;
}
