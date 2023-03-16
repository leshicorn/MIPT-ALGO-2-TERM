#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_QUEUE_SIZE 1000000

typedef struct queue {
    long long int data[MAX_QUEUE_SIZE];
    long long int front;
    long long int rear;
} Queue;

void initialize(Queue *q) {
    q->front = 0;
    q->rear = -1;
}

long long int is_empty(Queue *q) {
    return (q->front > q->rear);
}

long long int is_full(Queue *q) {
    return (q->rear == MAX_QUEUE_SIZE - 1);
}

void enqueue(Queue *q, long long int data) {
    if (is_full(q)) {
        printf("error\n");
        return;
    }
    q->rear++;
    q->data[q->rear] = data;
    printf("ok\n");
}

long long int dequeue(Queue *q) {
    if (is_empty(q)) {
        printf("error\n");
        return -1;
    }
    long long int data = q->data[q->front];
    q->front++;
    return data;
}

long long int front(Queue *q) {
    if (is_empty(q)) {
        printf("error\n");
        return -1;
    }
    return q->data[q->front];
}

long long int size(Queue *q) {
    return (q->rear - q->front + 1);
}

void clear(Queue *q) {
    initialize(q);
    printf("ok\n");
}

int main() {
    Queue q;
    initialize(&q);
    long long int min = INT_MAX;

    long long int n;
    char cmd[10];
    while (scanf("%s", cmd) != EOF) {
        if (strcmp(cmd, "enqueue") == 0) {
            if (scanf("%lld", &n) != 1) {
                printf("error\n");
                return -1;
            }
            enqueue(&q, n);
            if (n < min) {
                min = n;
            }
        } else if (strcmp(cmd, "dequeue") == 0) {
            long long int data = dequeue(&q);
            if (data != -1) {
                printf("%lld\n", data);
                }
            if (data != -1 && data == min) {
                min = INT_MAX;
                for (long long int i = q.front; i <= q.rear; i++) {
                    if (q.data[i] < min) {
                        min = q.data[i];
                    }
                }
            }
        } else if (strcmp(cmd, "front") == 0) {
            long long int data = front(&q);
            if (data != -1) {
                printf("%lld\n", data);
            }
        } else if (strcmp(cmd, "size") == 0) {
            printf("%lld\n", size(&q));
        } else if (strcmp(cmd, "clear") == 0) {
            clear(&q);
            min = INT_MAX;
        } else if (strcmp(cmd, "min") == 0) {
            if (is_empty(&q)) {
                printf("error\n");
            } else {
                printf("%lld\n", min);
            }
        }
    }

    return 0;
}