/**
 * Problem:
 * You are given an array of k linked-lists lists, each linked-list is sorted
 * in ascending order.
 *
 * Merge all the linked-lists into one sorted linked-list and return it.
 *
 * Solution:
 * Use a min-heap priority queue of capacity k. Push the head of each
 * non-NULL list into the heap, then repeatedly pop the minimum node,
 * append it to the result, and push its next node if non-NULL. A dummy
 * head simplifies result list construction and is freed before returning.
 *
 * Time Complexity:  O(n log k) -> each of the n nodes is pushed and popped
 *                   once, each operation costs O(log k)
 * Space Complexity: O(k) -> heap holds at most one node per list at a time
 */
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

typedef struct {
    struct ListNode **items;
    int size;
    int capacity;
} pqueue;

void swap(struct ListNode **a, struct ListNode **b)
{
    struct ListNode *temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_up(pqueue *pq, int index)
{
    int idx = (index - 1) / 2;
    while (index && pq->items[idx]->val > pq->items[index]->val) {
        swap(&pq->items[idx], &pq->items[index]);
        heapify_up(pq, idx);
    }
}

void enqueue(pqueue *pq, struct ListNode *item)
{
    if (pq->size == pq->capacity || item == NULL) {
        return;
    }

    pq->items[pq->size++] = item;
    heapify_up(pq, pq->size - 1);
}

void heapify_down(pqueue *pq, int index)
{
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < pq->size && pq->items[left]->val < pq->items[smallest]->val) {
        smallest = left;
    }
    if (right < pq->size && pq->items[right]->val < pq->items[smallest]->val) {
        smallest = right;
    }
    if (smallest != index) {
        swap(&pq->items[index], &pq->items[smallest]);
        heapify_down(pq, smallest);
    }
}

struct ListNode *dequeue(pqueue *pq)
{
    if (pq->size == 0) {
        return NULL;
    }

    struct ListNode *item = pq->items[0];
    pq->items[0] = pq->items[--pq->size];
    heapify_down(pq, 0);
    return item;
}

struct ListNode *mergeKLists(struct ListNode **lists, int listsSize)
{
    pqueue pq = {NULL, 0, listsSize};
    pq.items = calloc(pq.capacity, sizeof(struct ListNode *));
    struct ListNode *head = calloc(1, sizeof(struct ListNode));
    struct ListNode *curr = head;

    for (int i = 0; i < listsSize; i++) {
        if (lists[i] != NULL) {
            enqueue(&pq, lists[i]);
        }
    }

    while (pq.size > 0) {
        struct ListNode *dequeued = dequeue(&pq);
        if (dequeued->next != NULL) {
            enqueue(&pq, dequeued->next);
        }
        curr->next = dequeued;
        curr = curr->next;
    }

    struct ListNode *ret = head->next;
    free(head);
    free(pq.items);
    return ret;
}

int main(void)
{
    struct ListNode n1_3 = {5, NULL};
    struct ListNode n1_2 = {4, &n1_3};
    struct ListNode n1_1 = {1, &n1_2};

    struct ListNode n2_3 = {4, NULL};
    struct ListNode n2_2 = {3, &n2_3};
    struct ListNode n2_1 = {1, &n2_2};

    struct ListNode n3_2 = {6, NULL};
    struct ListNode n3_1 = {2, &n3_2};

    struct ListNode **lists = calloc(3, sizeof(struct ListNode *));
    lists[0] = &n1_1; // 1 -> 4 -> 5
    lists[1] = &n2_1; // 1 -> 3 -> 4
    lists[2] = &n3_1; // 2 -> 6

    struct ListNode *res = mergeKLists(lists, 3);
    return EXIT_SUCCESS;
}
