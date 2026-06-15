#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
    int items[MAX_SIZE];
    int size;
} pqueue;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_up(pqueue *pq, int index) {
    int idx = (index - 1) / 2; 
    if (index && pq->items[idx] > pq->items[index]) {
        swap(&pq->items[idx], &pq->items[index]);
        heapify_up(pq, idx);
    }
}

void enqueue(pqueue *pq, int value) {
    if (pq->size == MAX_SIZE) {
        return;
    }

    pq->items[pq->size++] = value;
    heapify_up(pq, pq->size - 1);
}

void heapify_down(pqueue *pq, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < pq->size && pq->items[left] < pq->items[smallest]) {
        smallest = left;
    }

    if (right < pq->size && pq->items[right] < pq->items[smallest]) {
        smallest = right;
    }

    if (smallest != index) {
        swap(&pq->items[index], &pq->items[smallest]);
        heapify_down(pq, smallest);
    }
}

int dequeue(pqueue *pq) {
    if (pq->size == 0) {
        return -1;
    }

    int item = pq->items[0];
    pq->items[0] = pq->items[--pq->size];
    heapify_down(pq, 0);
    return item;
}

int peek(pqueue *pq) {
    if (pq->size == 0) {
        return -1;
    }
    return pq->items[0];
}

int main(void)
{
    pqueue pq = {{0}, 0};

    enqueue(&pq, 3);
    enqueue(&pq, 2);
    enqueue(&pq, 15);
    enqueue(&pq, 5);
    enqueue(&pq, 4);
    enqueue(&pq, 45);
    
    return EXIT_SUCCESS;
}
