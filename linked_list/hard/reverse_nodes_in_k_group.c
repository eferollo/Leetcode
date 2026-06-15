/**
 * Problem:
 * Given the head of a linked list, reverse the nodes of the list k at a time,
 * and return the modified list.
 *
 * k is a positive integer and is less than or equal to the length of the linked
 * list. If the number of nodes is not a multiple of k then left-out nodes, in
 * the end, should remain as it is.
 *
 * You may not alter the values in the list's nodes, only nodes themselves may
 * be changed.
 *
 * Solution:
 * Process the list one group of k nodes at a time. For each group, probe
 * forward k steps to verify a full group remains. If fewer than k nodes
 * are left, stop and leave them untouched. Otherwise, reverse the k nodes
 * in isolation and stitch the result back into the list via two pointers:
 *   1. prev_tail (the last confirmed node of the already-processed result)
 *   2. probe (which already sits at the next group's start after the count
 *             loop)
 *
 * After reversal, group_start becomes group_tail which is the new prev_tail for
 * the next iteration. A stack-allocated dummy node avoids special-casing
 * the first group: prev_tail starts as dummy, so the first stitch sets
 * dummy->next to the first reversed group's head, which is returned.
 *
 * Time Complexity:  O(n)
 * Space Complexity: O(1)
 */
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode *reverse(struct ListNode *head, int k)
{
    struct ListNode *curr = head, *prev = NULL, *next = NULL;
    int n = 0;

    while (n != k && curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
        n++;
    }

    return prev;
}

struct ListNode *reverseKGroup(struct ListNode *head, int k)
{
    struct ListNode dummy = {0, head};
    /* last node of already-processed result, next group stitches here */
    struct ListNode *prev_tail = &dummy;
    struct ListNode *group_start = head;

    while (group_start != NULL) {
        /* probe forward k steps to check if a full group remains */
        struct ListNode *probe = group_start;
        int count = 0;
        while (count < k && probe != NULL) {
            probe = probe->next;
            count++;
        }
        /* fewer than k nodes remain, leave them as-is */
        if (count < k) {
            break;
        }

        /* group_start will become the tail after reversal */
        struct ListNode *group_tail = group_start;
        struct ListNode *new_head = reverse(group_start, k);

        /* stitch reversed group onto previous tail */
        prev_tail->next = new_head;
        /* stitch group tail onto the next group (probe is already there) */
        group_tail->next = probe;

        /* advance: group_tail is now the last confirmed node in the result */
        prev_tail = group_tail;
        group_start = probe;
    }

    return dummy.next;
}

int main(void)
{
    struct ListNode n5 = {5, NULL};
    struct ListNode n4 = {4, &n5};
    struct ListNode n3 = {3, &n4};
    struct ListNode n2 = {2, &n3};
    struct ListNode n1 = {1, &n2};

    reverseKGroup(&n1, 2);
    return EXIT_SUCCESS;
}
