/**
 * You are given an array of strings tokens that represents an arithmetic
 * expression in a Reverse Polish Notation.
 *
 * Evaluate the expression. Return an integer that represents the value of the
 * expression.
 *
 * Note that:
 *  The valid operators are '+', '-', '*', and '/'.
 *  Each operand may be an integer or another expression.
 *  The division between two integers always truncates toward zero.
 *  There will not be any division by zero.
 *  The input represents a valid arithmetic expression in a reverse polish
 *  notation.
 *  The answer and all the intermediate calculations can be represented
 *  in a 32-bit integer.
 *
 *  Example 1:
 *
 *  Input: tokens = ["2","1","+","3","*"]
 *  Output: 9
 *  Explanation: ((2 + 1) * 3) = 9
 *
 * Solution:
 * We use a stack to evaluate the Reverse Polish Notation expression.
 * We iterate through the tokens: if the token is a number, we push it
 * onto the stack; if it is an operator, we pop the top two elements (first b
 * then a), apply the operation, and push the result back onto the stack. The
 * final result is the last element remaining in the stack.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */

#include <stdlib.h>
#include <string.h>

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
    x->arr = calloc(capacity, sizeof(int));
    x->capacity = capacity;

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
    if (is_full(st)) {
        st->capacity *= 2;
        st->arr = realloc(st->arr, st->capacity * sizeof(int));
    }

    st->arr[++st->top] = val;
}

int pop(stack st)
{
    if (is_empty(st)) {
        return -1;
    }

    int popped = st->arr[st->top];
    st->top--;
    return popped;
}

int is_op(char *tok)
{
    if (strlen(tok) > 1) {
        return 0;
    }

    switch (*tok) {
    case '*':
    case '/':
    case '+':
    case '-':
        return 1;
    default:
        return 0;
    }
}

int make_op(int a, int b, char op)
{
    switch (op) {
    case '*':
        return a * b;
    case '/':
        return a / b;
    case '+':
        return a + b;
    case '-':
        return a - b;
    default:
        return -1;
    }
}

void stack_free(stack st)
{
    if (st == NULL) {
        return;
    }

    free(st->arr);
    free(st);
}

int evalRPN(char **tokens, int tokensSize)
{
    stack st = init(tokensSize);
    int i, res = 0;
    int a, b;

    for (i = 0; i < tokensSize; i++) {
        if (!is_op(tokens[i])) {
            push(st, atoi(tokens[i]));
        } else {
            b = pop(st);
            a = pop(st);
            push(st, make_op(a, b, *tokens[i]));
        }
    }

    res = pop(st);
    stack_free(st);
    return res;
}

int main(void)
{
    char *tokens[] = {"2", "1", "+", "3", "*"};
    int res = evalRPN(tokens, 5);
    return EXIT_SUCCESS;
}
