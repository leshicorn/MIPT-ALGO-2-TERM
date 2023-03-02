#include <stdio.h>
#include <stdlib.h>



struct stack
{
    int *arr;
    int top;
    int size;
};

struct stack *create_stack(int size)
{
    struct stack *s = (struct stack *)malloc(sizeof(struct stack));
    s->arr = (int *)malloc(sizeof(int) * size);
    s->top = -1;
    s->size = size;
    return s;
}

void push(struct stack *s, int data)
{
    if (s->top == s->size - 1)
    {
        printf("Stack Overflow\n");
        return;
    }
    s->arr[++s->top] = data;
}

int pop(struct stack *s)
{
    if (s->top == -1)
    {
        printf("Stack Underflow\n");
        return -1;
    }
    return s->arr[s->top--];
}

int peek(struct stack *s)
{
    if (s->top == -1)
    {
        printf("Stack Underflow\n");
        return -1;
    }
    return s->arr[s->top];
}

int is_empty(struct stack *s)
{
    return s->top == -1;
}

int main()
{
    
}