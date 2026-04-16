#include <stdio.h>
#include <stdlib.h>

struct hash_entry {
    int key;
    int value;
    struct hash_entry *next;
};

struct hash_table {
    size_t size;
    struct hash_entry **entries;
};
typedef struct hash_table *ht_t;

int hash(ht_t ht, int val)
{
    return abs(val) % ht->size;
}

ht_t ht_init(size_t size)
{
    ht_t x = calloc(1, sizeof(struct hash_table));
    if (x == NULL) {
        return NULL;
    }

    x->size = size;
    x->entries = calloc(size, sizeof(struct hash_entry *));
    if (x->entries == NULL) {
        free(x);
        return NULL;
    }

    return x;
}

void ht_free(ht_t ht)
{
    size_t i;
    if (ht == NULL) {
        return;
    }

    for (i = 0; i < ht->size; i++) {
        struct hash_entry *entry = ht->entries[i];
        while (entry) {
            struct hash_entry *temp = entry;
            entry = entry->next; 
            free(temp);    
        }
    }
    free(ht->entries);
    free(ht);
}

struct hash_entry *alloc_entry(int key, int value, struct hash_entry *next)
{
    struct hash_entry *x = calloc(1, sizeof(struct hash_entry));
    if (x == NULL) {
        return NULL;
    }

    x->key = key;
    x->value = value;
    x->next = next;
    return x;
}

struct hash_entry *ht_search(ht_t ht, int key)
{
    int hash_val = hash(ht, key);
    struct hash_entry *entry = ht->entries[hash_val];
    while (entry) {
        if (entry->key == key) {
            return entry;
        }
        entry = entry->next;
    }
    return NULL;
}

void ht_add(ht_t ht, int key, int value)
{
    int hash_val = hash(ht, key);
    struct hash_entry *new_entry = alloc_entry(key, value, ht->entries[hash_val]);
    ht->entries[hash_val] = new_entry;
}

void ht_print(ht_t ht)
{
    size_t i;
    printf("Hash Table (size: %ld)\n", ht->size);

    for (i = 0; i < ht->size; i++) {
        if (ht->entries[i]) {
            printf("[%ld]: ", i);
            struct hash_entry *entry = ht->entries[i];
            while (entry) {
                printf("(%d: %d) -> ", entry->key, entry->value);
                entry = entry->next;
            }
            printf("\n");
        }
    }
}

int main(void)
{
    ht_t ht = ht_init(10);

    if (ht == NULL) {
        return EXIT_FAILURE;
    }

    ht_add(ht, 10, 200);
    ht_add(ht, 30, 34);
    ht_add(ht, 33, 11);
    ht_add(ht, 67, 22);
    ht_add(ht, 122, 66);

    ht_print(ht);

    struct hash_entry *entry = ht_search(ht, 30);
    if (entry != NULL) {
        printf("Found\n");
    } else {
        printf("Not found\n");
    }

    ht_free(ht);
    ht = NULL;

    return EXIT_SUCCESS;
}
