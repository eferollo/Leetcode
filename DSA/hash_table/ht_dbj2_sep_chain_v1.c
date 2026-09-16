#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 16
#define LOAD_FACTOR      0.75

struct ht_entry {
    char *key;
    int value;
    struct ht_entry *next;
};

struct ht_t {
    struct ht_entry **entries;
    size_t capacity;
    size_t length;
};
typedef struct ht_t *ht;

void resize_table(ht table);
void ht_insert(ht table, const char *key, int value);

/* Hash function using dbj2 algorithm */
unsigned long hash(const char *key)
{
    unsigned long hash = 5381;
    int c;
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash;
}

ht ht_init()
{
    ht x = calloc(1, sizeof(struct ht_t));
    if (x == NULL) {
        return NULL;
    }
    x->capacity = INITIAL_CAPACITY;
    x->length = 0;

    x->entries = calloc(x->capacity, sizeof(struct ht_entry *));
    if (x->entries == NULL) {
        free(x);
        return NULL;
    }
    return x;
}

void ht_destroy(ht table)
{
    size_t i;
    for (i = 0; i < table->capacity; i++) {
        struct ht_entry *entry = table->entries[i];
        while (entry) {
            struct ht_entry *temp = entry;
            entry = entry->next;
            free(temp->key);
            free(temp);
        }
    }
    free(table->entries);
    free(table);
}

void resize_table(ht table)
{
    size_t old_size = table->capacity;
    size_t i;
    struct ht_entry **old_entries = table->entries;

    table->capacity *= 2;
    table->length = 0;
    table->entries = calloc(table->capacity, sizeof(struct ht_entry *));

    for (i = 0; i < old_size; i++) {
        struct ht_entry *entry = old_entries[i];
        while (entry) {
            ht_insert(table, entry->key, entry->value);
            entry = entry->next;
        }
    }

    for (i = 0; i < table->capacity; i++) {
        struct ht_entry *entry = old_entries[i];
        while (entry) {
            struct ht_entry *temp = entry;
            entry = entry->next;
            free(temp->key);
            free(temp);
        }
    }
    free(old_entries);
}

void ht_insert(ht table, const char *key, int value)
{
    if ((float)table->length / table->capacity > LOAD_FACTOR) {
        resize_table(table);
    }

    unsigned long hash_val = hash(key) % table->capacity;
    struct ht_entry *entry = table->entries[hash_val];

    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            entry->value = value;
            return;
        }
        entry = entry->next;
    }

    struct ht_entry *new_entry = calloc(1, sizeof(struct ht_entry *));
    new_entry->key = calloc(strlen(key) + 1, sizeof(char));
    strcpy(new_entry->key, key);
    new_entry->value = value;
    new_entry->next = table->entries[hash_val];
    table->entries[hash_val] = new_entry;
    table->length++;
}

int lookup(ht table, const char *key, int *found)
{
    unsigned long hash_val = hash(key) % table->capacity;
    struct ht_entry *entry = table->entries[hash_val];

    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            *found = 1;
            return entry->value;
        }
        entry = entry->next;
    }

    *found = 0;
    return 0;
}

int delete(ht table, const char *key)
{
    unsigned long hash_val = hash(key) % table->capacity;
    struct ht_entry *entry = table->entries[hash_val];
    struct ht_entry *prev = NULL;

    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            if (prev) {
                prev->next = entry->next;
            } else {
                table->entries[hash_val] = entry->next;
            }
            free(entry->key);
            free(entry);
            table->length--;
            return 1;
        }
        prev = entry;
        entry = entry->next;
    }

    return 0;
}

void print_table(ht table)
{
    size_t i;
    printf("Hash Table (capacity: %ld, length: %ld, load: %.2f%%)\n",
           table->capacity,
           table->length,
           (float)table->length / table->capacity * 100);

    for (i = 0; i < table->capacity; i++) {
        if (table->entries[i]) {
            printf("[%ld]: ", i);
            struct ht_entry *entry = table->entries[i];
            while (entry) {
                printf("(%s: %d) -> ", entry->key, entry->value);
                entry = entry->next;
            }
            printf("\n");
        }
    }
}

int main(void)
{

    ht table = ht_init();

    ht_insert(table, "abcd", 10);
    ht_insert(table, "defg", 11);
    ht_insert(table, "hdjhajdh", 3);
    ht_insert(table, "feafefaawf", 56);
    ht_insert(table, "defg", 12);

    print_table(table);

    return 0;
}
