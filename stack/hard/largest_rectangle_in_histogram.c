/**
 * Problem:
 * Given an array of integers heights representing the histogram's bar height
 * where the width of each bar is 1, return the area of the largest rectangle in
 * the histogram.
 *
 * Solution:
 * We use a monotonic increasing stack (array-based) storing indices of bars.
 * The stack maintains indices such that their heights are in non-decreasing
 * order.
 *
 * The key idea is: for each bar, we want to compute the largest rectangle where
 * this bar is the minimum height. This determines the maximum area it can
 * form.
 *
 * We iterate through the array:
 * - For each index i, while the current height is smaller than the height at
 *   the top of the stack, we pop the stack.
 * - When popping an index idx, we know:
 *     - The current index i is the first smaller bar on the right
 *     - The new top of the stack is the first smaller bar on the left
 * - Using these boundaries, we compute the width:
 *     width = (stack empty) ? i : i - peek(st) - 1
 * - Then compute area = heights[idx] * width and update the maximum.
 *
 * After the traversal, we process remaining indices in the stack:
 * - These bars extend to the end of the array as no smaller element exists
 *   on the right.
 *
 * Why it works:
 * - Each bar is pushed once and popped once
 * - When a bar is popped, we have found the widest range where it is the
 *   smallest bar, so its maximum rectangle is known
 *
 * Example:
 * heights = [2, 1, 5, 6, 2, 3]
 *
 * i=0 -> push 0                        -> stack: [0]
 * i=1 -> 1 < 2 -> pop 0 -> area=2*1=2  -> push 1 -> stack: [1]
 * i=2 -> 5 > 1 -> push 2               -> stack: [1,2]
 * i=3 -> 6 > 5 -> push 3               -> stack: [1,2,3]
 * i=4 -> 2 < 6 -> pop 3 -> area=6*1=6
 *      -> 2 < 5 -> pop 2 -> area=5*2=10
 *      -> push 4                        -> stack: [1,4]
 * i=5 -> 3 > 2 -> push 5               -> stack: [1,4,5]
 *
 * End:
 * pop 5 -> area=3*1=3
 * pop 4 -> area=2*4=8
 * pop 1 -> area=1*6=6
 *
 * Max area = 10
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */

#include <stdlib.h>

struct stack_s {
    int *arr;
    int capacity;
    int top;
};
typedef struct stack_s *stack;

stack init(int capacity)
{
    stack x = calloc(1, sizeof(struct stack_s));
    x->top = -1;
    x->capacity = capacity;
    x->arr = calloc(capacity, sizeof(int));

    return x;
}

int is_empty(stack st)
{
    return st->top == -1;
}

int is_full(stack st)
{
    return st->top >= st->capacity - 1;
}

void push(stack st, int val)
{
    if (st == NULL) {
        return;
    }

    if (is_full(st)) {
        st->capacity *= 2;
        st->arr = realloc(st->arr, st->capacity * sizeof(int));
    }

    st->arr[++st->top] = val;
}

int pop(stack st)
{
    if (st == NULL || is_empty(st)) {
        return -1;
    }

    int popped = st->arr[st->top];
    st->top--;
    return popped;
}

int peek(stack st)
{
    if (st == NULL || is_empty(st)) {
        return -1;
    }

    return st->arr[st->top];
}

int largestRectangleArea(int *heights, int heightsSize)
{
    stack st = init(heightsSize);
    int i, idx, width, area = 0;

    for (i = 0; i < heightsSize; i++) {
        while (!is_empty(st) && heights[i] < heights[peek(st)]) {
            idx = pop(st);
            width = is_empty(st) ? i : i - peek(st) - 1;
            if (heights[idx] * width > area) {
                area = heights[idx] * width;
            }
        }
        push(st, i);
    }

    int tmp;
    while (!is_empty(st)) {
        idx = pop(st);
        tmp = is_empty(st) ? (heights[idx] * heightsSize)
                           : (heights[idx] * (heightsSize - peek(st) - 1));
        if (tmp > area) {
            area = tmp;
        }
    }

    free(st->arr);
    free(st);
    return area;
}

int main(void)
{
    int heights[] = {2, 1, 5, 6, 2, 3};
    int res = largestRectangleArea(heights, 6);
    return EXIT_SUCCESS;
}
