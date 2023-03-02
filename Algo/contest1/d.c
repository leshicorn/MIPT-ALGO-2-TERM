#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 200001

long long int queue[MAX_QUEUE_SIZE]; // internal queue
long long int front_idx = 0; // index of the first element in the queue
long long int back_idx = 0; // index of the next free slot in the queue
long long int min_value = 1e9; // the smallest value seen so far

void enqueue(long long int x) {
    queue[back_idx++] = x;
    printf("ok\n");
    if (x < min_value) {
        min_value = x;
    }
}

void dequeue() {
    if (front_idx == back_idx) {
        printf("error\n");
    } else {
        printf("%lld\n", queue[front_idx++]);
        if (front_idx == back_idx) { // if the queue becomes empty
            front_idx = 0;
            back_idx = 0;
            min_value = 1e9;
        } else if (queue[front_idx] == min_value) { // if the smallest element is dequeued
            min_value = queue[front_idx+1];
            for (long long int i = front_idx+2; i < back_idx; i++) {
                if (queue[i] < min_value) {
                    min_value = queue[i];
                }
            }
        }
    }
}

void front() {
    if (front_idx == back_idx) {
        printf("error\n");
    } else {
        printf("%lld\n", queue[front_idx]);
    }
}

void size() {
    printf("%lld\n", back_idx - front_idx);
}

void clear() {
    front_idx = 0;
    back_idx = 0;
    min_value = 1e9;
    printf("ok\n");
}

void find_min() {
    if (front_idx == back_idx) {
        printf("error\n");
    } else {
        printf("%lld\n", min_value);
    }
}

int main() {
    long long int m;
    long long int input_amo = scanf("%lld", &m);
    if (input_amo != 1) {
        printf("error");
        return 0;
    }
    for (long long int i = 0; i < m; i++) {
        char* cmd = calloc(21, sizeof(char));
        if (scanf("%s", cmd) != 1) {
            printf("error");
            return 0;
        }
        if (strncmp(cmd, "enqueue", 7) == 0) {
            long long int x = 0;
            if (scanf("%lld", &x) != 1) {
                printf("error");
                return 0;
            }
            enqueue(x);
        } else if (strncmp(cmd, "dequeue", 7) == 0) {
            dequeue();
        } else if (strncmp(cmd, "front", 5) == 0) {
            front();
        } else if (strncmp(cmd, "size", 4) == 0) {
            size();
        } else if (strncmp(cmd, "clear", 5) == 0) {
            clear();
        } else if (strncmp(cmd, "min", 3) == 0) {
            find_min();
        }
    }
    return 0;
}
