/*
 * Problem:
 * Given an unsorted array of integers nums, return the length of the longest
 * consecutive elements sequence.
 *
 * You must write an algorithm that runs in O(n) time.
 *
 * Example:
 * Input: nums = [100,4,200,1,3,2]
 * Output: 4
 * Explanation: The longest consecutive elements sequence is [1, 2, 3, 4].
 * Therefore its length is 4.
 *
 * Solution:
 * We use a hash set to store all unique numbers for O(1) average lookup.
 * For each number in the set, we only start building a sequence if it is the
 * beginning of a sequence (i.e., num - 1 does not exist in the set).
 * Then we expand forward (num + 1, num + 2, ...) while elements exist
 * in the set, counting the length of the sequence.
 * This ensures each sequence is processed only once.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */

#include <stdlib.h>

struct node_s {
    int key;
    struct node_s *next;
};

struct hash_table_t {
    struct node_s **nodes;
    unsigned int size;
};
typedef struct hash_table_t *ht_t;

struct node_s *new_node(int key)
{
    struct node_s *x = calloc(1, sizeof(struct node_s));
    x->key = key;
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

unsigned long hash(int key, ht_t ht)
{
    return abs(key) % ht->size;
}

void ht_insert(int key, ht_t ht)
{
    if (ht == NULL) {
        return;
    }

    unsigned long hash_val = hash(key, ht);
    struct node_s *current = ht->nodes[hash_val];

    while (current) {
        if (current->key == key) {
            return;
        }
        current = current->next;
    }

    struct node_s *new = new_node(key);
    new->next = ht->nodes[hash_val];
    ht->nodes[hash_val] = new;
}

int ht_search(int key, ht_t ht)
{
    if (ht == NULL) {
        return 0;
    }

    unsigned long hash_val = hash(key, ht);
    struct node_s *current = ht->nodes[hash_val];

    while (current) {
        if (current->key == key) {
            return 1;
        }
        current = current->next;
    }

    return 0;
}

int longestConsecutive(int *nums, int numsSize)
{
    ht_t ht = ht_init(numsSize * 2);
    int max = 0;

    for (int i = 0; i < numsSize; i++) {
        ht_insert(nums[i], ht);
    }

    for (int i = 0; i < ht->size; i++) {
        struct node_s *current = ht->nodes[i];

        while (current != NULL) {
            int num = current->key;

            if (!ht_search(num - 1, ht)) {
                int curr = num;
                int len = 1;

                while (ht_search(curr + 1, ht)) {
                    curr++;
                    len++;
                }

                if (len > max) {
                    max = len;
                }
            }
            current = current->next;
        }
    }
    return max;
}

int main(void)
{
    int vec[6] = {100, 4, 200, 1, 3, 2};
    int max = longestConsecutive(vec, 6);
    return EXIT_SUCCESS;
}
