#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct Stack {
    Node *head;
    int num_elements;
} Stack;

Stack *create_stack() {
    Stack *stack = (Stack*)malloc(sizeof(Stack));
    stack->head = NULL;
    stack->num_elements = 0;
    return stack;
}

void push(Stack *stack, int value) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = stack->head;

    stack->head = new_node;
    stack->num_elements++;
}

int pop(Stack *stack) {
    if (stack->num_elements == 0) {
        return -1;
    }

    int temp = stack->head->value;
    stack->head = stack->head->next;
    stack->num_elements--;

    return temp;
}

int size(Stack *stack) {
    return stack->num_elements;
}

int is_empty(Stack *stack) {
    return stack->num_elements == 0;
}


void test1() {

Stack * top = create_stack();
    
    for (int i = 0; i < 1000000; i++) {
        push(top, i);
    }

    for (int i = 0; i < 500000; i++) {
        int value = pop(top);
    }

    for (int i = 0; i < 250000; i++) {
        push(top, i);
    }

    while (size(top) > 100000) {

        int size_s = size(top);

        for (int i = 0; i < size_s / 2; i++) {
            int value = pop(top);
        }

        for (int i = 0; i < size_s / 4; i++) {
            push(top, i);
        }
    }

}

void test2() {

    Stack * top = create_stack();

    for (int i = 0; i < 1000000; i++) {
        push(top, i);
    }

    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 10000; j++) {
            int value = pop(top);
        }
        for (int k = 0; k < 10000; k++) {
            push(top, k);
        }
    }

    while (size(top) > 100000) {
        int size_s = size(top);

        for (int i = 0; i < size_s / 2; i++) {
            int value = pop(top);
        }

        for (int i = 0; i < size_s / 4; i++) {
            push(top, i);
        }
    }

    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 10000; j++) {
            int value = pop(top);
        }
        for (int k = 0; k < 10000; k++) {
            push(top, k);
        }
    }
}

void test1_average_time() {
    double time_spent_test1_1 = 0.0;
    double time_spent_test1_2 = 0.0;
    double time_spent_test1_3 = 0.0;

    clock_t begin1 = clock();
    test1();
    clock_t end1 = clock();
    time_spent_test1_1 += (double)(end1 - begin1) / CLOCKS_PER_SEC;


    clock_t begin2 = clock();
    test1();
    clock_t end2 = clock();
    time_spent_test1_2 += (double)(end2 - begin2) / CLOCKS_PER_SEC;


    clock_t begin3 = clock();
    test1();
    clock_t end3 = clock();
    time_spent_test1_3 += (double)(end3 - begin3) / CLOCKS_PER_SEC;

    double time_spent_test1 = (time_spent_test1_1 + time_spent_test1_2 + time_spent_test1_3) / 3.0;

    printf("The elapsed time of TEST 1 is %f seconds\n\n", time_spent_test1);

    return;
}

void test2_average_time() {
    double time_spent_test2_1 = 0.0;
    double time_spent_test2_2 = 0.0;
    double time_spent_test2_3 = 0.0;

    clock_t begin1 = clock();
    test1();
    clock_t end1 = clock();
    time_spent_test2_1 += (double)(end1 - begin1) / CLOCKS_PER_SEC;


    clock_t begin2 = clock();
    test1();
    clock_t end2 = clock();
    time_spent_test2_2 += (double)(end2 - begin2) / CLOCKS_PER_SEC;


    clock_t begin3 = clock();
    test1();
    clock_t end3 = clock();
    time_spent_test2_3 += (double)(end3 - begin3) / CLOCKS_PER_SEC;

    double time_spent_test1 = (time_spent_test2_1 + time_spent_test2_2 + time_spent_test2_3) / 3.0;

    printf("The elapsed time of TEST 2 is %f seconds\n\n", time_spent_test1);

    return;
}

void test3_average_time() {
    double time_spent_test3 = 0.0;

    for (int i = 0; i < 3; i++) {
        Stack * top = create_stack();

        for (int i = 0; i < 1000000; i++) {
            push(top, i);
        }
        
        clock_t begin = clock();

        for (int i = 0; i < 1000000; i++) {
            int rand_v = rand() % 2;

            if (rand_v == 0)
            {
                push(top, i);
            }
            else
            {
                int value = pop(top);
            }
        }

        clock_t end = clock();
        time_spent_test3 += (double)(end - begin) / CLOCKS_PER_SEC;
    }

    time_spent_test3 /= 3.0;
    printf("The elapsed time of TEST 3 is %f seconds\n\n", time_spent_test3);
    
    return;
}

void average_time_test() {
    test1_average_time();
    test2_average_time();
    test3_average_time();
}

int main() {
    average_time_test();
}