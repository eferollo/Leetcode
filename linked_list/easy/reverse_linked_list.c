/**
 * Problem:
 * Given the head of a singly linked list, reverse the list, and return the
 * reversed list.
 *
 * Solution:
 * We reverse the linked list in-place by iterating through it once.
 * At each step, we take the current node and flip its pointer to point
 * to the previous node instead of the next one.
 *
 * To do this safely, we always keep track of three pointers:
 * - prev: the already reversed part of the list
 * - curr: the current node we are processing
 * - next: the next node to visit (so we don’t lose the rest of the list)
 *
 * Process:
 * 1. Save the next node (next = curr->next)
 * 2. Reverse the current node's pointer (curr->next = prev)
 * 3. Move prev and curr forward (prev = curr, curr = next)
 *
 * After the loop finishes, prev will point to the new head of the reversed
 * list.
 *
 * Key intuition to remember:
 * "Detach current node and attach it in front of the reversed list."
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
#include <stdlib.h>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode *new_node(int val, struct ListNode *next)
{
    struct ListNode *x = calloc(1, sizeof(struct ListNode));
    x->val = val;
    x->next = next;

    return x;
}

struct ListNode *reverseList(struct ListNode *head)
{
    struct ListNode *current = head, *next = NULL, *prev = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    return prev;
}

int main(void)
{

    struct ListNode *list =
        new_node(1, new_node(2, new_node(3, new_node(4, new_node(5, NULL)))));

    struct ListNode *res = reverseList(list);
    return EXIT_SUCCESS;
}
