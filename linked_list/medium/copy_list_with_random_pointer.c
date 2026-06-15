/**
 * Problem:
 * Given the head of a linked list of length n, where each node holds an integer
 * val and two pointers — next and random — deep-copy the list and return the
 * head of the copy. next points to the following node or NULL; random points to
 * any node in the list or NULL. Every node in the copy must be freshly
 * allocated; no pointer in the copied list may point into the original list.
 *
 * Solution:
 * Three-pass O(1)-space interleaving approach:
 *   1. Interleave — for each original node X, insert a copy X' between X
 *      and X->next, so the list becomes X->X'->Y->Y'->...
 *   2. Random wiring — for each original node X, set X'->random =
 *      X->random->next (the copy of X's random target sits immediately after
 *      it).
 *   3. Extraction — unlink the copy nodes to restore the original list and
 *      build the copied list.
 *
 * Time Complexity:  O(n)
 * Space Complexity: O(1)
 */
#include <stdlib.h>

struct Node {
    int val;
    struct Node *next;
    struct Node *random;
};

struct Node *new_node(int val, struct Node *next, struct Node *random)
{
    struct Node *x = calloc(1, sizeof(struct Node));
    if (x == NULL) {
        return NULL;
    }
    x->val = val;
    x->next = next;
    x->random = random;
    return x;
}

struct Node *copyRandomList(struct Node *head)
{
    struct Node *current = head;
    struct Node *new = NULL;

    if (head == NULL) {
        return NULL;
    }

    while (current != NULL) {
        current->next = new_node(current->val, current->next, NULL);
        current = current->next->next;
    }

    current = head;
    while (current != NULL) {
        current->next->random =
            current->random == NULL ? NULL : current->random->next;
        current = current->next->next;
    }

    current = head->next;
    new = current;
    while (current != NULL) {
        current->next = current->next == NULL ? NULL : current->next->next;
        current = current->next;
    }

    return new;
}

int main(void)
{
    struct Node *n4 = new_node(1, NULL, NULL);
    struct Node *n3 = new_node(10, n4, NULL);
    struct Node *n2 = new_node(11, n3, NULL);
    struct Node *n1 = new_node(13, n2, NULL);
    struct Node *n0 = new_node(7, n1, NULL);

    n0->random = NULL;
    n1->random = n0;
    n2->random = n4;
    n3->random = n2;
    n4->random = n0;

    struct Node *copy = copyRandomList(n0);

    return EXIT_SUCCESS;
}
