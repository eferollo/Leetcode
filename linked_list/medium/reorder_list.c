/**
 * Problem: Reorder a singly linked list from L0→L1→…→Ln into
 *          L0→Ln→L1→Ln-1→L2→Ln-2→..., modifying only node pointers.
 *
 * Solution: Push all nodes onto a stack, then interleave from both ends:
 *           at each step, splice the top-of-stack node after the current
 *           front node, then advance the front pointer to what was its
 *           original next. Stop when the two pointers meet (odd length)
 *           or cross (even length).
 *
 * Time Complexity:  O(n)
 * Space Complexity: O(n)
 */
#include <stdlib.h>
#include <stdbool.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct stack {
    struct ListNode **arr;
    int top;
    size_t capacity;
};

bool is_full(struct stack *st) {
    return st->top == st->capacity - 1;
}

bool is_empty(struct stack *st) {
    return st->top == -1;
} 

void stack_push(struct stack *st, struct ListNode *node) {
    if (st == NULL) {
        return;
    }

    if (is_full(st)) {
        st->capacity *= 2;
        st->arr = realloc(st->arr, st->capacity * sizeof(struct ListNode *));
    }

    st->arr[++st->top] = node;
}

struct ListNode *stack_pop(struct stack *st) {
    if (st == NULL || is_empty(st)) {
        return NULL;
    }

    struct ListNode *popped = st->arr[st->top];
    st->top--;
    return popped;
}

void stack_init(struct stack *st) {
    if (st == NULL) {
        return;
    }
    st->top = -1;
    st->capacity = 5;
    st->arr = calloc(st->capacity, sizeof(struct ListNode *));
}

void reorderList(struct ListNode* head) {
    struct stack st;
    stack_init(&st);

    struct ListNode *current = head;
    while (current != NULL) {
        stack_push(&st, current);
        current = current->next;
    }

    current = head;
    while (current != NULL) {
        struct ListNode *old_next = current->next;
        struct ListNode *popped = NULL;
        popped = stack_pop(&st);
        if (popped == NULL || popped == current) {
            current->next = NULL;
            break;
        }

        if (popped == old_next) {
            popped->next = NULL;
            break;
        }
        current->next = popped;
        popped->next = old_next;
        current = old_next;
    }
    free(st.arr);
}

int main(void)
{
    struct ListNode n5 = {5, NULL};
    struct ListNode n4 = {4, &n5};
    struct ListNode n3 = {3, &n4};
    struct ListNode n2 = {2, &n3};
    struct ListNode n1 = {1, &n2};

    reorderList(&n1);
    return EXIT_SUCCESS;
}
