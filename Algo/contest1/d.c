#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_QUEUE_SIZE 200005

int queue[MAX_QUEUE_SIZE];
int front = 0;
int rear = -1;
int size = 0;
int min = INT_MAX;

void enqueue(int n) {
    rear++;
    queue[rear] = n;
    size++;
    if (n < min) {
        min = n;
    }
    printf("ok\n");
}

void dequeue() {
    if (size == 0) {
        printf("error\n");
        return;
    }
    printf("%d\n", queue[rear]);
    front--;
    size--;
    if (size == 0) {
        min = INT_MAX;
    } else if (queue[rear] == min) {
        min = queue[rear - 1];
        for (int i = rear - 1; i >= front; i--) {
            if (queue[i] < min) {
                min = queue[i];
            }
        }
    }
}

void front_element() {
    if (size == 0) {
        printf("error\n");
        return;
    }
    printf("%d\n", queue[front]);
}

void queue_size() {
    printf("%d\n", size);
}

void clear_queue() {
    front = 0;
    rear = -1;
    size = 0;
    min = INT_MAX;
    printf("ok\n");
}

void min_element() {
    if (size == 0) {
        printf("error\n");
        return;
    }
    printf("%d\n", min);
}

int main() {
    int m;
    char op[10];
    int n;
    if (scanf("%d", &m) != 1) {
        printf("Error");
        return -1;
    }
    for (int i = 0; i < m; i++) {
        if (scanf("%s", op) != 1) {
            printf("Error");
            return -1;
        }
        if (strcmp(op, "enqueue") == 0) {
            if (scanf("%d", &n) != 1) {
                printf("Error");
                return -1;
            }
            enqueue(n);
        } else if (strcmp(op, "dequeue") == 0) {
            dequeue();
        } else if (strcmp(op, "front") == 0) {
            front_element();
        } else if (strcmp(op, "size") == 0) {
            queue_size();
        } else if (strcmp(op, "clear") == 0) {
            clear_queue();
        } else if (strcmp(op, "min") == 0) {
            min_element();
        }
    }
    return 0;
}
