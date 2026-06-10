/**
 * Problem:
 * Design a time-based key-value data structure that supports storing
 * multiple values for the same key at different timestamps and retrieving
 * the value at a given timestamp.
 *
 * Implement the TimeMap with the following operations:
 *
 * - TimeMap():
 *   Initialize the data structure.
 *
 * - void set(char* key, char* value, int timestamp):
 *   Store the given key with the associated value at the specified timestamp.
 *
 * - char* get(char* key, int timestamp):
 *   Return the value associated with the largest timestamp <= given timestamp.
 *   If multiple values satisfy this condition, return the one with the
 *   greatest timestamp. If no such value exists, return an empty string "".
 *
 * Solution:
 * We implement a hash map where each key maps to a node containing:
 * - an array of values
 * - a parallel array of timestamps (strictly increasing)
 *
 * For set():
 * - Use hashing to locate the bucket
 * - Traverse the linked list to find the key (handle collisions)
 * - Append (value, timestamp) to the node arrays (resize if needed)
 *
 * For get():
 * - Use hashing to find the node for the key
 * - Perform binary search on the timestamps array to find the
 *   largest timestamp <= target
 * - Return the corresponding value (or "" if none exists)
 *
 * This works because timestamps are inserted in increasing order,
 * so binary search is valid and efficient.
 *
 * Time Complexity: O(log n) for binary search
 * Space Complexity: O(n)
 */
#include <stdlib.h>
#include <string.h>

struct node_s {
    char *key;
    char **values;
    int *timestamps;
    int size;
    int capacity;
    struct node_s *next;
};

typedef struct {
    struct node_s **nodes;
    unsigned int size;
} TimeMap;

TimeMap *timeMapCreate()
{
    TimeMap *x = calloc(1, sizeof(TimeMap));
    if (x == NULL) {
        return NULL;
    }
    x->size = 10007;
    x->nodes = calloc(x->size, sizeof(struct node_s *));
    if (x->nodes == NULL) {
        free(x);
        return NULL;
    }

    return x;
}

struct node_s *new_node(char *key)
{
    struct node_s *x = calloc(1, sizeof(struct node_s));
    if (x == NULL) {
        return NULL;
    }

    x->key = strdup(key);
    if (x->key == NULL) {
        free(x);
        return NULL;
    }
    x->capacity = 4;
    x->size = 0;
    x->values = calloc(x->capacity, sizeof(char *));
    if (x->values == NULL) {
        free(x);
        return NULL;
    }
    x->timestamps = calloc(x->capacity, sizeof(int));
    if (x->timestamps == NULL) {
        free(x->values);
        free(x);
        return NULL;
    }
    x->next = NULL;

    return x;
}

unsigned long hash(char *key, TimeMap *obj)
{
    unsigned long hash = 0;
    while (*key) {
        hash = (hash * 31 + *(key++)) % obj->size;
    }
    return hash;
}

void insert_value(struct node_s *node, char *value, int timestamp)
{
    if (node == NULL) {
        return;
    }

    if (node->size == node->capacity) {
        node->capacity *= 2;
        node->timestamps =
            realloc(node->timestamps, node->capacity * sizeof(int));
        node->values = realloc(node->values, node->capacity * sizeof(char *));
    }

    node->values[node->size] = strdup(value);
    node->timestamps[node->size] = timestamp;
    node->size++;
}

void timeMapSet(TimeMap *obj, char *key, char *value, int timestamp)
{
    unsigned long hash_val = hash(key, obj);
    struct node_s *current = obj->nodes[hash_val];

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            insert_value(current, value, timestamp);
            return;
        }
        current = current->next;
    }

    struct node_s *new = new_node(key);
    insert_value(new, value, timestamp);

    new->next = obj->nodes[hash_val];
    obj->nodes[hash_val] = new;
}

char *get_value(struct node_s *node, int timestamp)
{
    int l = 0, r = node->size - 1, mid;

    while (l <= r) {
        mid = (l + r) / 2;

        if (node->timestamps[mid] == timestamp) {
            return node->values[mid];
        }

        if (node->timestamps[mid] < timestamp) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    // r is the last index with timestamp <= target
    if (r < 0) {
        return "";
    }

    return node->values[r];
}

char *timeMapGet(TimeMap *obj, char *key, int timestamp)
{
    unsigned long hash_val = hash(key, obj);
    struct node_s *current = obj->nodes[hash_val];

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return get_value(current, timestamp);
        }
        current = current->next;
    }

    return strdup("");
}

void timeMapFree(TimeMap *obj)
{
    if (obj == NULL) {
        return;
    }

    for (unsigned int i = 0; i < obj->size; i++) {
        struct node_s *current = obj->nodes[i];

        while (current != NULL) {
            struct node_s *next = current->next;
            free(current->key);
            for (int j = 0; j < current->size; j++) {
                free(current->values[j]);
            }
            free(current->values);
            free(current->timestamps);
            free(current);
            current = next;
        }
    }

    free(obj->nodes);
    free(obj);
}

/**
 * Your TimeMap struct will be instantiated and called as such:
 * TimeMap* obj = timeMapCreate();
 * timeMapSet(obj, key, value, timestamp);

 * char* param_2 = timeMapGet(obj, key, timestamp);

 * timeMapFree(obj);
*/

int main(void)
{
    TimeMap *timeMap = timeMapCreate();

    // output array (same order as example)
    char *output[7];

    // ["TimeMap", "set", "get", "get", "set", "get", "get"]

    output[0] = NULL;

    timeMapSet(timeMap, "foo", "bar", 1);
    output[1] = NULL;

    output[2] = timeMapGet(timeMap, "foo", 1); // "bar"
    output[3] = timeMapGet(timeMap, "foo", 3); // "bar"

    timeMapSet(timeMap, "foo", "bar2", 4);
    output[4] = NULL;

    output[5] = timeMapGet(timeMap, "foo", 4); // "bar2"
    output[6] = timeMapGet(timeMap, "foo", 5); // "bar2"

    timeMapFree(timeMap);
    return EXIT_SUCCESS;
}
