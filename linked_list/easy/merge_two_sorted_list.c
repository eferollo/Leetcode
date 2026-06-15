/**
 * Problem:
 * You are given the heads of two sorted linked lists list1 and list2.
 * Merge the two lists into one sorted list. The list should be made by
 * splicing together the nodes of the first two lists.
 *
 * Return the head of the merged linked list.
 *
 * Solution:
 * Create a dummy head node to simplify handling the head of the merged
 * list. Maintain a pointer to the last node of the merged list.
 * Compare the current nodes of list1 and list2, append the smaller node
 * to the merged list, and advance the corresponding list pointer.
 * Continue until one list becomes empty, then attach the remaining nodes
 * of the other list since they are already sorted.
 *
 * Time Complexity: O(n + m)
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

struct ListNode *mergeTwoLists(struct ListNode *list1, struct ListNode *list2)
{
    struct ListNode head = {0, NULL};
    struct ListNode *p = &head;
    while (list1 != NULL && list2 != NULL) {
        if (list1->val < list2->val) {
            p->next = list1;
            list1 = list1->next;
        } else {
            p->next = list2;
            list2 = list2->next;
        }
        p = p->next;
    }

    if (list1 == NULL) {
        p->next = list2;
    } else if (list2 == NULL) {
        p->next = list1;
    }
    return head.next;
}

int main(void)
{
    struct ListNode n1_3 = {4, NULL};
    struct ListNode n1_2 = {2, &n1_3};
    struct ListNode n1_1 = {1, &n1_2};

    struct ListNode n2_3 = {5, NULL};
    struct ListNode n2_2 = {3, &n2_3};
    struct ListNode n2_1 = {1, &n2_2};

    struct ListNode *list1 = &n1_1; // 1 -> 2 -> 4
    struct ListNode *list2 = &n2_1; // 1 -> 3 -> 5

    struct ListNode *res = mergeTwoLists(list1, list2);
    return EXIT_SUCCESS;
}
