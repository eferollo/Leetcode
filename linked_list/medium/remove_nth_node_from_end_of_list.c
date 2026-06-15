/**
 * Problem:
 * Given the head of a linked list, remove the nth node from the end of the
 * list and return its head.
 *
 * Solution:
 * Two-pointer technique: advance p2 by n steps ahead of p1, then move both
 * until p2 reaches the last node. At that point p1 is the node just before
 * the target, so splice it out via p1->next = p1->next->next.
 * Edge case: if p2 is already NULL after the initial advance, the target is
 * the head node, so return head->next directly.
 *
 * Time Complexity:  O(n)
 * Space Complexity: O(1)
 */
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode *removeNthFromEnd(struct ListNode *head, int n)
{
    struct ListNode *p1 = head, *p2 = p1, *copy = head;

    if (p1 == NULL || p1->next == NULL) {
        return NULL;
    }

    for (int i = 0; i < n && p2 != NULL; i++) {
        p2 = p2->next;
    }

    if (p2 == NULL) {
        return copy->next;
    }

    while (p1 != NULL && p2 != NULL) {
        p2 = p2->next;
        if (p2 == NULL) {
            p1->next = p1->next->next;
            break;
        }
        p1 = p1->next;
    }
    return copy;
}

int main(void)
{
    struct ListNode n5 = {5, NULL};
    struct ListNode n4 = {4, &n5};
    struct ListNode n3 = {3, &n4};
    struct ListNode n2 = {2, &n3};
    struct ListNode n1 = {1, &n2};

    struct ListNode *res = removeNthFromEnd(&n1, 2);

    return EXIT_SUCCESS;
}
