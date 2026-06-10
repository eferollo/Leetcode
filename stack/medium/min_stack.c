/**
 * Design a stack that supports push, pop, top, and retrieving the minimum
 * element in constant time.
 *
 * Implement the MinStack class:
 * 1. MinStack() initializes the stack object.
 * 2. void push(int val) pushes the element val onto the stack.
 * 3. void pop() removes the element on the top of the stack.
 * 4. int top() gets the top element of the stack.
 * 5. int getMin() retrieves the minimum element in the stack.
 *
 * You must implement a solution with O(1) time complexity for each function.
 *
 * Solution:
 * We implement a stack where each node stores both its value and the minimum
 * value up to that point in the stack. When pushing a new element, we compare
 * it with the current minimum (from the previous top) and store the updated
 * minimum alongside the value. This allows retrieving the minimum element
 * in constant time without traversing the stack.
 *
 * Time Complexity: O(1)
 * Space Complexity: O(n)
 */
#include <stdlib.h>

struct node {
    int val;
    int min;
};

typedef struct {
    struct node **arr;
    int top;
    int capacity;
} MinStack;

MinStack *minStackCreate()
{
    MinStack *x = calloc(1, sizeof(MinStack));
    if (x == NULL) {
        return NULL;
    }
    x->top = -1;
    x->capacity = 1000;
    x->arr = calloc(x->capacity, sizeof(struct node *));
    if (x->arr == NULL) {
        free(x);
        return NULL;
    }

    return x;
}

int is_full(MinStack *obj)
{
    return obj->top == obj->capacity - 1;
}

int is_empty(MinStack *obj)
{
    return obj->top == -1;
}

void minStackPush(MinStack *obj, int val)
{
    int min;
    if (obj == NULL) {
        return;
    }

    if (is_full(obj)) {
        obj->capacity *= 2;
        obj->arr = realloc(obj->arr, obj->capacity * sizeof(struct node *));
    }

    if (is_empty(obj)) {
        min = val;
    } else {
        min = obj->arr[obj->top]->min; 
    }

    obj->arr[++obj->top] = calloc(1, sizeof(struct node));
    obj->arr[obj->top]->val = val;
    if (val < min) {
        obj->arr[obj->top]->min = val;
    } else {
        obj->arr[obj->top]->min = min;
    }
}

void minStackPop(MinStack *obj)
{
    if (obj == NULL || is_empty(obj)) {
        return;
    }

    obj->top--;
}

int minStackTop(MinStack *obj) {
    if (obj == NULL || is_empty(obj)) {
        return -1;
    }

    return obj->arr[obj->top]->val;
}

int minStackGetMin(MinStack *obj) {
    if (obj == NULL || is_empty(obj)) {
        return -1;
    }

    return obj->arr[obj->top]->min;
}

void minStackFree(MinStack *obj) {
    if (obj == NULL) {
        return;
    }

    for (int i = 0; i < obj->capacity; i++) {
        if (obj->arr[i] != NULL) {
            free(obj->arr[i]);
        }
    }
    free(obj->arr);
    free(obj);
}

/**
 * Your MinStack struct will be instantiated and called as such:
 * MinStack* obj = minStackCreate();
 * minStackPush(obj, val);

 * minStackPop(obj);

 * int param_3 = minStackTop(obj);

 * int param_4 = minStackGetMin(obj);

 * minStackFree(obj);
*/
