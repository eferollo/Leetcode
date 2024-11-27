typedef struct stack_s{
    int *arr;
    int top;
    int size;
} stack_t;

void stack_init(stack_t *stack, int size) {
    stack->arr = calloc(size, sizeof(int));
    stack->top = -1;
    stack->size = size;
}

void stack_free(stack_t *stack) {
    free(stack->arr);
}

int is_full(stack_t *stack) {
    return stack->top == (stack->size-1);
}

int is_empty(stack_t *stack) {
    return stack->top == -1;
}

void push(stack_t *stack, int value) {
    if (is_full(stack)) {
        return;
    } 
    stack->arr[++stack->top] = value;
}

int pop(stack_t *stack) {
    if (is_empty(stack)) {
        return -1;
    }
    int popped = stack->arr[stack->top];
    stack->top--;
    return popped;
}

int is_operand(char *ch) {
    if (strlen(ch) > 1) {
        return 0;
    }
    if (*ch == '*' || *ch == '/' || *ch == '+' || *ch == '-') 
        return 1;
    return 0;
} 

int make_op(int a, int b, char op) {
    switch(op) {
        case '+':
            return a+b;
        case '-':
            return a-b;
        case '*':
            return a*b;
        case '/':
            return a/b;
        default:
            return -1;
    }
}

int evalRPN(char** tokens, int tokensSize) {
    int i, a, b, res, rv;

    /* Initialize stack */
    stack_t stack;
    stack_init(&stack, tokensSize);

    for (i = 0; i < tokensSize; i++) {
        if (!is_operand(tokens[i])) {
            push(&stack, atoi(tokens[i]));
        } else {
            b = pop(&stack);
            a = pop(&stack);
            res = make_op(a, b, *tokens[i]);
            push(&stack, res);
        }
    }

    rv = pop(&stack);
    stack_free(&stack);

    return rv; 
}
