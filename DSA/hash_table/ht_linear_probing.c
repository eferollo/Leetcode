#include <stdlib.h>

typedef enum { EMPTY = 0, OCCUPIED, DELETED } entry_state;

struct ht_entry {
    int key;
    int val;
    entry_state state;
};

typedef struct {
    struct ht_entry *entries;
    size_t capacity;
    size_t size;
} ht_t;

/*
 * Load factor = size / capacity. With linear probing, probe chains grow
 * as the table fills; at load factor 0.5 average probe length stays near 1.
 * So we allocate 2*capacity slots to ensure load factor never exceeds 0.5.
 * We then round up to the next power of two so the bitmask trick in hash()
 * stays valid.
 */
size_t ht_size(size_t capacity)
{
    size_t s = 1;
    while (s < 2 * capacity) {
        s <<= 1;
    }
    return s;
}

int ht_init(ht_t *ht, size_t capacity)
{
    if (ht == NULL) {
        return -1;
    }

    ht->capacity = ht_size(capacity);
    ht->entries = calloc(ht->capacity, sizeof(struct ht_entry));
    if (ht->entries == NULL) {
        return -1;
    }
    return 0;
}

unsigned long hash(ht_t *ht, int key)
{
    return (unsigned long)key & (ht->capacity - 1);
}

int ht_resize(ht_t *ht)
{
    if (ht == NULL) {
        return -1;
    }
    size_t new_capacity = ht->capacity * 2;
    struct ht_entry *new_entries =
        calloc(new_capacity, sizeof(struct ht_entry));
    if (new_entries == NULL) {
        return -1;
    }

    /* rehash all OCCUPIED entries */
    for (size_t i = 0; i < ht->capacity; i++) {
        if (ht->entries[i].state == OCCUPIED) {
            unsigned long j =
                (unsigned long)ht->entries[i].key & (new_capacity - 1);
            while (new_entries[j].state == OCCUPIED) {
                j = (j + 1) & (new_capacity - 1);
            }
            new_entries[j] = ht->entries[i];
        }
    }

    free(ht->entries);
    ht->entries = new_entries;
    ht->capacity = new_capacity;
    return 0;
}

int ht_add(ht_t *ht, int key, int val)
{
    if (ht->size > ht->capacity / 2) {
        int rc = ht_resize(ht);
        if (rc == -1) {
            return -1;
        }
    }

    unsigned long i = hash(ht, key);
    while (ht->entries[i].state == OCCUPIED && ht->entries[i].key != key) {
        i = (i + 1) & (ht->capacity - 1);
    }
    ht->entries[i].key = key;
    ht->entries[i].val = val;
    ht->entries[i].state = OCCUPIED;
    ht->size++;
    return 0;
}

int ht_delete(ht_t *ht, int key)
{
    if (ht->size == 0) {
        return -1;
    }

    unsigned long i = hash(ht, key);
    while (ht->entries[i].state != EMPTY) {
        if (ht->entries[i].state == OCCUPIED && ht->entries[i].key == key) {
            ht->entries[i].state = DELETED;
            ht->size--;
            return 0;
        }
        i = (i + 1) & (ht->capacity - 1);
    }
    return -1;
}

int ht_get(ht_t *ht, int key)
{
    if (ht->size == 0) {
        return -1;
    }

    unsigned long i = hash(ht, key);
    while (ht->entries[i].state == OCCUPIED) {
        if (ht->entries[i].key == key) {
            return ht->entries[i].val;
        }
        i = (i + 1) & (ht->capacity - 1);
    }
    return -1;
}

void ht_free(ht_t *ht)
{
    if (ht == NULL) {
        return;
    }
    free(ht->entries);
}

int main(void)
{
    ht_t ht;
    int rc = ht_init(&ht, 1000);

    if (rc == -1) {
        return EXIT_FAILURE;
    }

    ht_add(&ht, 10, 200);
    ht_add(&ht, 30, 34);
    ht_add(&ht, 33, 11);
    ht_add(&ht, 67, 22);
    ht_add(&ht, 122, 66);

    int res = ht_get(&ht, 122);

    ht_free(&ht);

    return EXIT_SUCCESS;
}
