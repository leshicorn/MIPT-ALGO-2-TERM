#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAXLEN 129

/**
 * @brief Структура стека
 * @details data - массив данных; size - настоящий размер; allocated_size - выделенное количество памяти; elem_size - размер конкретного элемента
 * 
 */
typedef struct stack
{
    size_t allocated_size;
    size_t size;
    size_t elem_size;
    void * data;
} stack;

int ft_isnan(const double a)
{
	return a != a;
}

struct stack* stack_new(size_t elem_size)
{
    assert(elem_size);
    struct stack* stack = (struct stack*)malloc(sizeof(struct stack) * 1);
    
    stack->data = (void *)malloc(1 * elem_size * sizeof(char));
    stack->size = 0;
    stack->allocated_size = 1;
    stack->elem_size = elem_size;
    return stack;
}

int stack_push(struct stack* st, const void * elem)
{
    assert(st);
    assert(elem);
    
    if (st->size == st->allocated_size)
    {
        st->allocated_size *= 2;
        st->data = realloc(st->data, (st->allocated_size) * (st->elem_size));
        if (st->data == NULL)
            return 1;
    }
    memcpy(st->data + ((st->size) * (st->elem_size)), elem, st->elem_size);
    st->size = st->size + 1;
    return 0;
}

int stack_pop(struct stack* st, void * elem)
{
    assert(st);
    assert(elem);

    if (st->size != 0)
    {
        memcpy(elem, st->data + (st->size - 1) * (st->elem_size), st->elem_size);
        st->size--;    
        return 0;
    }
    return 1;
}

int stack_top(struct stack* st, void * elem)
{
    assert(st);
    assert(elem);

    if (st->size != 0)
    {
        memcpy(elem, (st->data) + (st->size - 1) * (st->elem_size), st->elem_size);
        return 0;
    }
    return 1;
}

int stack_empty(struct stack const * st)
{
    assert(st);

    if (st == NULL)
        return 1;
    if (st->size == 0)
        return 1;
    return 0;
}

struct stack* stack_delete(struct stack* st)
{
    assert(st);

    free(st->data);
    free(st);

    return NULL;
}

void stack_print(struct stack const * st, void (*pf) (void const * st))
{
    assert(st);

    printf("[");
    for(size_t i = 0; i != st->size; i++)
    {
        pf(st->data + st->elem_size * i);
        if (i != st->size - 1)
            printf(", ");
    }
    printf("]\n");
}

int main()
{
    stack* arr = stack_new(sizeof(int));
    char* input = (char*)malloc(sizeof(char) * MAXLEN);
    char sep[10] = " ,\n";

    while (strcmp(input, "exit") != 0)
    {
        scanf("%s", input);

        if (strncmp(input, "push", 4))
        {

        }
        if (strncmp(input, "pop", 3))
        {
            
        }
        if (strncmp(input, "back", 4))
        {
            
        }
        if (strncmp(input, "size", 4))
        {
            
        }
        if (strncmp(input, "clear", 5))
        {
            
        }
        if (strncmp(input, "exit", 4))
        {
            
        }
    }
}