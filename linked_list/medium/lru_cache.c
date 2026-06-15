/**
 * Problem:
 * Implement the LRUCache class:
 *
 * - LRUCache(int capacity) Initialize the LRU cache with positive size
 *   capacity.
 *
 * - int get(int key) Return the value of the key if the key exists, otherwise
 *   return -1.
 *
 * - void put(int key, int value) Update the value of the key if the key exists.
 *   Otherwise, add the key-value pair to the cache. If the number of keys
 *   exceeds the capacity from this operation, evict the least recently used
 *   key. The functions get and put must each run in O(1) average time
 *   complexity.
 *
 * Solution:
 * Combine a doubly-linked list and a hash map with linear probing.
 * The list tracks recency: head is MRU, tail is LRU. The hash map maps
 * each key to its list node for O(1) lookup.
 *
 * get(key):
 *   - look up the node in the hash map
 *   - if not found return -1
 *   - otherwise detach the node from its current position and reinsert
 *     it at the head (MRU), then return its value.
 *
 * put(key, value):
 *   - if the key already exists, update its value, detach and reinsert
 *     at head
 *   - otherwise, if the cache is full, evict tail->key: remove it from
 *     the list, delete it from the hash map, free its node
 *   - allocate a new node, push it to the head, insert it into the hash map
 *
 * Collision resolution uses linear probing with tombstoning (DELETED state)
 * so that probe chains remain intact after deletion. Hash table capacity is
 * the next power of two >= 2*lru_capacity, keeping load factor <= 0.5.
 *
 * Time Complexity:  O(1) average for get and put
 * Space Complexity: O(n) —> n list nodes + 2n hash table slots
 */
#include <stdlib.h>

/* Doubly-linked list to keep track of MRU and LRU */
struct node_s {
    int key;
    int val;
    struct node_s *next;
    struct node_s *prev;
};

/* HashMap (linear probing) to achieve O(1) insertion and deletion */
typedef enum { EMPTY = 0, OCCUPIED, DELETED } entry_state;

struct ht_entry {
    int key;
    struct node_s *val;
    entry_state state;
};

typedef struct {
    struct ht_entry *entries;
    size_t capacity;
} ht_t;

/* LRU cache */
typedef struct {
    ht_t ht;             // HashMap key-value (value is a pointer to node)
    struct node_s *head; // MRU
    struct node_s *tail; // LRU
    size_t capacity;     // capacity of LRU cache
    size_t size;         // Counter of elems in the cache
} LRUCache;

/* ------------- Double-linked list ------------------------ */
void list_remove(LRUCache *obj, struct node_s *node)
{
    /* If not at head update prev->next, otherwise update the head */
    if (node->prev != NULL) {
        node->prev->next = node->next;
    } else {
        obj->head = node->next;
    }

    /* If not at the tail update next->prev, otherwise update the tail */
    if (node->next != NULL) {
        node->next->prev = node->prev;
    } else {
        obj->tail = node->prev;
    }
}

void list_push_front(LRUCache *obj, struct node_s *node)
{
    node->prev = NULL;
    node->next = obj->head;
    if (obj->head != NULL) {
        /* If head already exists update prev with the current node */
        obj->head->prev = node;
    } else {
        /* list was empty */
        obj->tail = node;
    }
    obj->head = node; // current node becomes MRU
}
/* -------------------------------------------------------- */

/* ------------ Hash Table w/ linear probing -------------- */
/*
 * Load factor = size / capacity. With linear probing, probe chains grow
 * as the table fills; at load factor 0.5 average probe length stays near 1.
 * So we allocate 2*capacity slots to ensure load factor never exceeds 0.5.
 * We then round up to the next power of two so the bitmask trick in hash()
 * stays valid.
 */
size_t ht_size(size_t capacity)
{
    /* next power of two >= 2*capacity */
    size_t s = 1;
    while (s < 2 * capacity) {
        s <<= 1;
    }
    return s;
}

int ht_init(ht_t *ht, size_t capacity)
{
    ht->capacity = capacity;
    ht->entries = calloc(capacity, sizeof(struct ht_entry));
    if (ht->entries == NULL) {
        return -1;
    }
    return 0;
}

/*
 * Capacity is a power of two, so (capacity - 1) is a bitmask of all ones
 * in the lower bits (e.g. capacity=8 -> 0b0111). ANDing with it is
 * equivalent to key % capacity but avoids a division. The (unsigned long)
 * cast prevents undefined behavior on negative keys.
 */
unsigned long hash(ht_t *ht, int key)
{
    return (unsigned long)key & (ht->capacity - 1);
}

struct node_s *ht_get(ht_t *ht, int key)
{
    unsigned long i = hash(ht, key);
    while (ht->entries[i].state == OCCUPIED) {
        if (ht->entries[i].key == key) {
            return ht->entries[i].val;
        }
        i = (i + 1) & (ht->capacity - 1); // i++ % capacity
    }
    return NULL;
}

void ht_put(ht_t *ht, int key, struct node_s *val)
{
    unsigned long i = hash(ht, key);
    while (ht->entries[i].state == OCCUPIED && ht->entries[i].key != key) {
        i = (i + 1) & (ht->capacity - 1);
    }
    ht->entries[i].key = key;
    ht->entries[i].val = val;
    ht->entries[i].state = OCCUPIED;
}

void ht_delete(ht_t *ht, int key)
{
    unsigned long i = hash(ht, key);
    while (ht->entries[i].state != EMPTY) {
        if (ht->entries[i].state == OCCUPIED && ht->entries[i].key == key) {
            ht->entries[i].state = DELETED;
            return;
        }
        i = (i + 1) & (ht->capacity - 1);
    }
}
/* -------------------------------------------------------- */

/* -------------------- LRU cache ------------------------- */
LRUCache *lRUCacheCreate(int capacity)
{
    LRUCache *x = calloc(1, sizeof(*x));
    if (x == NULL) {
        return NULL;
    }
    x->capacity = capacity;
    int rc = ht_init(&x->ht, ht_size(x->capacity));
    if (rc == -1) {
        free(x);
        return NULL;
    }
    return x;
}

int lRUCacheGet(LRUCache *obj, int key)
{
    if (obj == NULL) {
        return -1;
    }

    struct node_s *node = ht_get(&obj->ht, key);
    if (node == NULL) {
        return -1;
    }

    list_remove(obj, node);
    list_push_front(obj, node);
    return node->val;
}

void lRUCachePut(LRUCache *obj, int key, int value)
{
    if (obj == NULL) {
        return;
    }

    struct node_s *node = ht_get(&obj->ht, key);
    if (node) {
        node->val = value;
        list_remove(obj, node);
        list_push_front(obj, node);
    } else {
        if (obj->size == obj->capacity) {
            int del_key = obj->tail->key;
            struct node_s *del_node = obj->tail;
            list_remove(obj, obj->tail);
            ht_delete(&obj->ht, del_key);
            free(del_node);
            obj->size--;
        }
        // allocate a new node
        node = calloc(1, sizeof(struct node_s));
        if (node == NULL) {
            return;
        }
        node->val = value;
        node->key = key; // important for eviction
        list_push_front(obj, node);
        ht_put(&obj->ht, key, node);
        obj->size++;
    }
}

void lRUCacheFree(LRUCache *obj)
{
    if (obj == NULL) {
        return;
    }

    struct node_s *current = obj->head;
    while (current != NULL) {
        struct node_s *next = current->next;
        free(current);
        current = next;
    }
    free(obj->ht.entries);
    free(obj);
}
/* -------------------------------------------------------- */

/**
 * Your LRUCache struct will be instantiated and called as such:
 * LRUCache* obj = lRUCacheCreate(capacity);
 * int param_1 = lRUCacheGet(obj, key);

 * lRUCachePut(obj, key, value);

 * lRUCacheFree(obj);
*/

int main(void)
{
    LRUCache *obj = lRUCacheCreate(2);

    lRUCachePut(obj, 1, 1); // cache: {1=1}
    lRUCachePut(obj, 2, 2); // cache: {1=1, 2=2}
    lRUCacheGet(obj, 1);    // return 1,  cache: {2=2, 1=1}
    lRUCachePut(obj, 3, 3); // evicts 2,  cache: {1=1, 3=3}
    lRUCacheGet(obj, 2);    // return -1 (not found)
    lRUCachePut(obj, 4, 4); // evicts 1,  cache: {3=3, 4=4}
    lRUCacheGet(obj, 1);    // return -1 (not found)
    lRUCacheGet(obj, 3);    // return 3
    lRUCacheGet(obj, 4);    // return 4

    lRUCacheFree(obj);
    return EXIT_SUCCESS;
}
