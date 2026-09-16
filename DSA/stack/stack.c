#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *arr;
    int top;
    size_t capacity; // we may use also fixed size and avoid resizing arr
} stack;

int stack_init(stack *st, size_t capacity) {
    if (st == NULL) {
        return -1;
    }
    st->capacity = capacity;
    st->arr = calloc(capacity, sizeof(int));
    if (st->arr == NULL) {
        return -1;
    }
    st->top = -1;
    return 0;
}

bool is_empty(stack *st) {
    return st->top == -1;
} 

bool is_full(stack *st) {
    return st->top == st->capacity - 1;
}

int peek(stack *st) {
    if (st == NULL || is_empty(st)) {
        return -1;
    }
    return st->arr[st->top];
}

int push(stack *st, int val) {
    if (st == NULL) {
        return -1;
    }

    if (is_full(st)) {
        st->capacity *= 2;
        st->arr = realloc(st->arr, st->capacity * sizeof(int));
        if (st->arr == NULL) {
            return -1;
        }
    }

    st->arr[++st->top] = val;
    return 0;
}

int pop(stack *st) {
    if (st == NULL || is_empty(st)) {
        return -1;
    }

    int popped = st->arr[st->top];
    st->top--;
    return popped;
}



