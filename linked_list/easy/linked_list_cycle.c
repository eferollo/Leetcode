/**
 * Problem:
 * Given the head of a linked list, determine whether the list contains
 * a cycle. A cycle exists if following next pointers repeatedly causes
 * a node to be visited again.
 *
 * Solution:
 * Use Floyd's Cycle Detection algorithm (Tortoise and Hare). Maintain
 * two pointers: a slow pointer that advances one node at a time and a
 * fast pointer that advances two nodes at a time. If a cycle exists,
 * the fast pointer will eventually catch up to the slow pointer. If the
 * fast pointer reaches NULL, the list does not contain a cycle.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
#include <stdbool.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

bool hasCycle(struct ListNode *head)
{
    if (head == NULL) {
        return false;
    }
    struct ListNode *p1 = head, *p2 = p1->next;
    while (p2 != NULL && p2->next != NULL) {
        if (p1 == p2) {
            return true;
        }
        p2 = p2->next->next;
        p1 = p1->next;
    }
    return false;
}

int main(void)
{
    struct ListNode n4 = {-4, NULL};
    struct ListNode n3 = {0, &n4};
    struct ListNode n2 = {2, &n3};
    struct ListNode n1 = {3, &n2};

    n4.next = &n2;
    bool res = hasCycle(&n1);
    return EXIT_SUCCESS;
}
