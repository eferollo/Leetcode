/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode *newNode(int val) {
    struct ListNode *x = calloc(1, sizeof(struct ListNode));
    x->val = val;
    x->next = NULL;
    return x;
}

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode *head = calloc(1, sizeof(struct ListNode));
    struct ListNode *current = head;
    int sum, carry = 0;

    while (l1 != NULL || l2 != NULL || carry > 0) {
        sum = carry;
        if (l1 != NULL) {
            sum += l1->val;
            l1 = l1->next;
        }
        if (l2 != NULL) {
            sum += l2->val;
            l2 = l2->next;
        }

        carry = sum / 10;
        current->next = newNode(sum % 10);
        current = current->next;
    }
    struct ListNode *ret = head->next;
    free(head);
    return ret;
}
