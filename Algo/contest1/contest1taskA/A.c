#include <stdio.h>
#include <string.h>


#define MAX_SIZE 10000

int stack[MAX_SIZE];
int top = -1;

void push(int n) {
    if (top == MAX_SIZE - 1) {
        printf("error\n");
    } else {
        stack[++top] = n;
        printf("ok\n");
    }
}

void pop() {
    if (top == -1) {
        printf("error\n");
    } else {
        printf("%d\n", stack[top--]);
    }
}

void back() {
    if (top == -1) {
        printf("error\n");
    } else {
        printf("%d\n", stack[top]);
    }
}

void size() {
    printf("%d\n", top + 1);
}

void clear() {
    top = -1;
    printf("ok\n");
}

int main() {
    char query[10];
    int n;

    while (scanf("%s", query) != EOF) {
        if (strcmp(query, "push") == 0) {
            if (scanf("%d", &n) != 1) {
                printf("error");
                return -1;
            }
            push(n);
        } else if (strcmp(query, "pop") == 0) {
            pop();
        } else if (strcmp(query, "back") == 0) {
            back();
        } else if (strcmp(query, "size") == 0) {
            size();
        } else if (strcmp(query, "clear") == 0) {
            clear();
        } else if (strcmp(query, "exit") == 0) {
            printf("bye\n");
            break;
        }
    }

    return 0;
}
