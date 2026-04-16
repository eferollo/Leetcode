/**
 * Given an integer array nums and an integer k, return the k most frequent
 * elements. You may return the answer in any order.
 *
 * Example 1:
 *
 * Input: nums = [1,1,1,2,2,3], k = 2
 *
 * Output: [1,2]
 *
 * Solution:
 * We first count the frequency of each element using a hash table.
 * Then, instead of sorting by frequency, we use a sort of bucket sort:
 * we create an array of buckets where the index represents the frequency,
 * and each bucket stores the elements with that frequency.
 *
 * Since the maximum possible frequency is numsSize, the bucket array has
 * size numsSize + 1. We place each element into its corresponding bucket
 * based on its frequency.
 *
 * Finally, we iterate the buckets from highest frequency to lowest and
 * collect the first k elements.
 *
 * This avoids sorting and achieves O(n) time complexity.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n) since k < n
 *
 */
#include <stdlib.h>

struct node_s {
    int key;
    int freq;
    struct node_s *next;
};

struct hash_table_t {
    struct node_s **nodes;
    unsigned int size;
};
typedef struct hash_table_t *ht_t;

unsigned long hash(int key, ht_t ht)
{
    return abs(key) % ht->size;
}

struct node_s *new_node(int key)
{
    struct node_s *x = calloc(1, sizeof(struct node_s));
    x->key = key;
    x->freq = 1;
    x->next = NULL;

    return x;
}

ht_t ht_init(unsigned int size)
{
    ht_t ht = calloc(1, sizeof(struct hash_table_t));
    ht->nodes = calloc(size, sizeof(struct node_s *));
    ht->size = size;

    return ht;
}

void ht_insert(int key, ht_t ht)
{
    unsigned long hash_val = hash(key, ht);
    struct node_s *current = ht->nodes[hash_val];

    while (current) {
        if (current->key == key) {
            current->freq++;
            return;
        }
        current = current->next;
    }

    struct node_s *new = new_node(key);
    new->next = ht->nodes[hash_val];
    ht->nodes[hash_val] = new;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *topKFrequent(int *nums, int numsSize, int k, int *returnSize)
{
    ht_t ht = ht_init(numsSize);

    int *res = calloc(k, sizeof(int));
    *returnSize = k;

    for (int i = 0; i < numsSize; i++) {
        ht_insert(nums[i], ht);
    }

    struct node_s **buckets = calloc(numsSize + 1, sizeof(struct node_s *));

    for (unsigned int i = 0; i < ht->size; i++) {
        struct node_s *current = ht->nodes[i];
        while (current) {
            int freq = current->freq;
            struct node_s *next = current->next;
            current->next = buckets[freq];
            buckets[freq] = current;
            current = next;
        }
    }

    int count = 0;
    for (int i = numsSize; i >= 0 && count < k; i--) {
        struct node_s *current = buckets[i];
        while (current && count < k) {
            res[count++] = current->key;
            current = current->next;
        }
    }

    return res;
}

int main(void)
{

    int nums[] = {1, 1, 1, 2, 2, 3};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int k = 2;
    int returnSize = 0;

    int *result = topKFrequent(nums, numsSize, k, &returnSize);
    return EXIT_SUCCESS;
}
