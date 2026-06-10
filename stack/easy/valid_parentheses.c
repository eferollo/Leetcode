/**
 * Given a string s containing just the characters '(', ')', '{', '}', '[' and
 * ']', determine if the input string is valid.
 *
 * An input string is valid if:
 * 1. Open brackets must be closed by the same type of brackets.
 * 2. Open brackets must be closed in the correct order.
 * 3. Every close bracket has a corresponding open bracket of the same type.
 *
 * Solution:
 * Use a stack to track opening brackets. Push each opening symbol,
 * and on a closing one, pop and verify it matches the expected type.
 * If any mismatch occurs or the stack is not empty at the end,
 * the string is invalid. Stack resizes dynamically if needed.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

struct stack_s {
    char *arr;
    int top;
    size_t capacity;
};
typedef struct stack_s *stack;

stack init(size_t capacity)
{
    stack x = calloc(1, sizeof(struct stack_s));
    if (x == NULL) {
        return NULL;
    }
    x->arr = calloc(capacity, sizeof(char));
    if (x->arr == NULL) {
        free(x);
        return NULL;
    }
    x->capacity = capacity;
    x->top = -1;

    return x;
}

bool is_empty(stack st)
{
    return st->top == -1;
}

bool is_full(stack st)
{
    return st->top >= st->capacity - 1;
}

void push(stack st, char val)
{
    if (is_full(st)) {
        st->capacity *= 2;
        st->arr = realloc(st->arr, st->capacity * sizeof(char));
    }

    st->arr[++st->top] = val;
}

char pop(stack st)
{
    if (is_empty(st)) {
        return '\0';
    }

    int popped = st->arr[st->top];
    st->top--;
    return popped;
}

/* not used */
char peek(stack st)
{
    if (is_empty(st)) {
        return '\0';
    }

    return st->arr[st->top];
}

void stack_free(stack st)
{
    if (st == NULL) {
        return;
    }
    free(st->arr);
    free(st);
}

bool isValid(char *s)
{
    size_t len = strlen(s), i;
    stack st = init(len);
    char popped;

    for (i = 0; i < len; i++) {
        switch (s[i]) {
        case '(':
        case '[':
        case '{':
            push(st, s[i]);
            break;
        case ')':
            popped = pop(st);
            if (popped != '(') {
                return false;
            }
            break;
        case ']':
            popped = pop(st);
            if (popped != '[') {
                return false;
            }
            break;
        case '}':
            popped = pop(st);
            if (popped != '{') {
                return false;
            }
            break;
        default:
            /*invalid char */
            return false;
        }
    }

    if (!is_empty(st)) {
        stack_free(st);
        return false;
    }

    stack_free(st);
    return true;
}

int main(void)
{
    char s[] = "([])";
    int res = isValid(s);
    return EXIT_SUCCESS;
}
