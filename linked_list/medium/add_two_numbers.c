/**
 * Problem:
 * You are given two non-empty linked lists representing two non-negative
 * integers. The digits are stored in reverse order, and each of their nodes
 * contains a single digit. Add the two numbers and return the sum as a linked
 * list.
 *
 * You may assume the two numbers do not contain any leading zero, except the
 * number 0 itself.
 *
 * Solution:
 * Iterate both lists simultaneously, summing corresponding digits plus any
 * carry from the previous step. At each position emit a new node with value
 * sum % 10 and propagate carry = sum / 10. Continue until both lists are
 * exhausted and carry is zero.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode *new_node(int val, struct ListNode *next)
{
    struct ListNode *x = calloc(1, sizeof(struct ListNode));
    if (x == NULL) {
        return NULL;
    }
    x->val = val;
    x->next = next;
    return x;
}

struct ListNode *addTwoNumbers(struct ListNode *l1, struct ListNode *l2)
{
    int sum, carry = 0;
    struct ListNode *head = new_node(0, NULL), *current = head;

    while (l1 != NULL || l2 != NULL || carry > 0) {
        sum = carry;
        if (l1 != NULL) {
            sum += l1->val;
            l1 = l1->next;
        } else if (l2 != NULL) {
            sum += l2->val;
            l2 = l2->next;
        }

        carry = sum / 10;

        current->next = new_node(sum % 10, NULL);
        current = current->next;
    }
    struct ListNode *ret = head->next;
    free(head);
    return ret;
}

int main(void)
{
    struct ListNode n3 = {3, NULL};
    struct ListNode n2 = {4, &n3};
    struct ListNode n1 = {2, &n2};

    struct ListNode _n3 = {4, NULL};
    struct ListNode _n2 = {6, &_n3};
    struct ListNode _n1 = {5, &_n2};

    struct ListNode *res = addTwoNumbers(&n1, &_n1);
    return EXIT_SUCCESS;
}
