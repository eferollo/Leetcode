/**
 * Problem:
 * Given an array of integers temperatures represents the daily temperatures,
 * return an array answer such that answer[i] is the number of days you have to
 * wait after the ith day to get a warmer temperature. If there is no future day
 * for which this is possible, keep answer[i] == 0 instead.
 *
 * Solution:
 * We use a monotonic decreasing stack (implemented with an array) that stores
 * indices of the temperatures array. The stack keeps indices whose temperatures
 * are in decreasing order from bottom to top.
 *
 * For each day i:
 * - While the current temperature is higher than the temperature at the index
 *   on top of the stack, we pop that index and compute the number of days
 *   waited: res[idx] = i - idx
 * - Then we push the current index onto the stack.
 *
 * This works because when a warmer day is found, it resolves all previous days
 * with lower temperatures that were waiting in the stack.
 *
 * Stack used:
 * - Array-based stack storing indices (not values)
 * - Monotonic decreasing stack (temperatures[stack[i]] >=
 *   temperatures[stack[i+1]])
 * - We store indices to compute distances (i - idx)
 *
 * Example:
 * temperatures = [73, 74, 75, 71, 69, 72, 76, 73]
 *
 * i=0 -> push 0                        -> stack: [0]
 * i=1 -> 74 > 73 -> pop 0 -> res[0]=1  -> push 1 -> stack: [1]
 * i=2 -> 75 > 74 -> pop 1 -> res[1]=1  -> push 2 -> stack: [2]
 * i=3 -> 71 < 75 -> push 3             -> stack: [2,3]
 * i=4 -> 69 < 71 -> push 4             -> stack: [2,3,4]
 * i=5 -> 72 > 69 -> pop 4 -> res[4]=1
 *      -> 72 > 71 -> pop 3 -> res[3]=2
 *      -> push 5                        -> stack: [2,5]
 * i=6 -> 76 > 72 -> pop 5 -> res[5]=1
 *      -> 76 > 75 -> pop 2 -> res[2]=4
 *      -> push 6                        -> stack: [6]
 * i=7 -> 73 < 76 -> push 7             -> stack: [6,7]
 *
 * Remaining indices (6,7) -> no warmer day -> res = 0 
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
    stack st = calloc(1, sizeof(struct stack_s));
    st->top = -1;
    st->capacity = capacity;
    st->arr = calloc(capacity, sizeof(int));
    return st;
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

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *dailyTemperatures(int *temperatures, int temperaturesSize, int *returnSize)
{
    *returnSize = temperaturesSize;
    int i, idx;
    int *res = calloc(temperaturesSize, sizeof(int));
    stack st = init(temperaturesSize);
    push(st, 0);

    for (i = 1; i < temperaturesSize; i++) {
        while (!is_empty(st) && temperatures[peek(st)] < temperatures[i]) {
            idx = pop(st);
            res[idx] = i - idx;
        }
        push(st, i);
    }

    free(st->arr);
    free(st);
    return res;
}

int main(void)
{
    int temp[] = {73, 74, 75, 71, 69, 72, 76, 73};
    int size;
    int *res = dailyTemperatures(temp, 8, &size);
    return EXIT_SUCCESS;
}
