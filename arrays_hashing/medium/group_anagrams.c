/**
 * Problem:
 * Given an array of strings strs, group the anagrams together.
 * You can return the answer in any order.
 *
 * Example 1:
 *
 * Input: strs = ["eat","tea","tan","ate","nat","bat"]
 *
 * Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
 *
 * Solution:
 * The optimal solution groups anagrams using a hash table. The key idea is
 * to sort each string in ascending order and use the resulting string as the
 * key in the hash map. For every input string, we first compute its sorted
 * form. If a node with the same key already exists, we append the original
 * string to that node’s “group” array, expanding it dynamically as needed.
 * Otherwise, we create a new node with this key and initialize its group with
 * the current string. Finally, we traverse the hash map and collect all the
 * grouped anagrams into the result.
 *
 * Sorting each string takes O(k*logk). Doing it for each string is
 * O(n*k*logk).
 *
 * Time Complexity: O(n*k*logk)
 * Space Complexity: O(n*k)
 */

#include <stdlib.h>
#include <string.h>

struct node_s {
    char *key;
    char **group;
    int size;
    int capacity;
    struct node_s *next;
};

struct hash_map_t {
    struct node_s **nodes;
    unsigned int size;
};
typedef struct hash_map_t *hm_t;

struct node_s *new_node(char *key)
{
    struct node_s *x = calloc(1, sizeof(struct node_s));
    if (x == NULL) {
        return NULL;
    }

    x->key = strdup(key);
    x->size = 0;
    x->capacity = 2;
    x->group = calloc(x->capacity, sizeof(char *));
    if (x->group == NULL) {
        free(x);
        return NULL;
    }
    x->next = NULL;

    return x;
}

unsigned long hash(char *str, hm_t hm)
{
    unsigned long hash = 0;
    while (*str) {
        hash = (hash * 31 + *(str++)) % hm->size;
    }
    return hash;
}

void add_to_group(struct node_s *node, char *str)
{
    if (str == NULL) {
        return;
    }

    if (node->size == node->capacity) {
        node->capacity *= 2;
        node->group = realloc(node->group, node->capacity * sizeof(char *));
    }

    node->group[node->size++] = str;
}

hm_t hm_init(unsigned int size)
{
    hm_t x = calloc(1, sizeof(struct hash_map_t));
    if (x == NULL) {
        return NULL;
    }

    x->size = size;
    x->nodes = calloc(size, sizeof(struct node_s *));
    if (x->nodes == NULL) {
        free(x);
        return NULL;
    }

    return x;
}

void hm_insert(char *key, char *orig_str, hm_t hm)
{
    if (hm == NULL) {
        return;
    }

    unsigned long hash_val = hash(key, hm);
    struct node_s *current = hm->nodes[hash_val];

    while (current) {
        if (strcmp(current->key, key) == 0) {
            add_to_group(current, orig_str);
            return;
        }
        current = current->next;
    }

    /* create a new node */
    struct node_s *new = new_node(key);
    add_to_group(new, orig_str);

    new->next = hm->nodes[hash_val];
    hm->nodes[hash_val] = new;
}

int compare(const void *a, const void *b)
{
    return (*(char *)a - *(char *)b);
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced,
 * assume caller calls free().
 */
char ***groupAnagrams(char **strs,
                      int strsSize,
                      int *returnSize,
                      int **returnColumnSizes)
{
    int j = 0;
    char *copy = NULL;

    hm_t hm = hm_init(10007);
    for (int i = 0; i < strsSize; i++) {
        copy = strdup(strs[i]);
        if (copy == NULL) {
            // free hm
            return NULL;
        }

        qsort(copy, strlen(copy), sizeof(char), compare);
        hm_insert(copy, strs[i], hm);
        free(copy);
    }

    int groups = 0;
    for (unsigned int i = 0; i < hm->size; i++) {
        struct node_s *current = hm->nodes[i];
        while (current) {
            groups++;
            current = current->next;
        }
    }

    char ***result = calloc(groups, sizeof(char **));
    *returnColumnSizes = calloc(groups, sizeof(int));

    for (unsigned int i = 0; i < hm->size; i++) {
        struct node_s *current = hm->nodes[i];
        while (current) {
            result[j] = current->group;
            (*returnColumnSizes)[j] = current->size;
            j++;
            current = current->next;
        }
    }

    *returnSize = groups;
    return result;
}
int main(void)
{
    char *strs[] = {"eat", "tea", "tan", "ate", "nat", "bat"};
    int size = 0;
    int *colsize = NULL;
    char ***result = groupAnagrams(strs, 6, &size, &colsize);
    return EXIT_SUCCESS;
}
