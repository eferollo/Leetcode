/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

struct node_s {
    int key;
    int value;
    struct node_s *next;
};

struct hashtable_s {
    int n;
    struct node_s **elems;
};
typedef struct hashtable_s *hash_t;

struct node_s *newNode(int key, int value, struct node_s *next) {
    struct node_s *x = calloc(1, sizeof(struct node_s));
    if (x == NULL) {
        return NULL;
    }

    x->key = key;
    x->value = value;
    x->next = next;

    return x;
}

hash_t hash_table_init(int size) {
    hash_t x = calloc(1, sizeof(struct hashtable_s));
    if (x == NULL) {
        return NULL;
    }

    x->elems = calloc(size, sizeof(struct node_s *));
    if (x->elems == NULL) {
        return NULL;
    }

    x->n = size;
    return x;
}

int hash_func(int key, int size) {
    return abs(key) % size;
}

void insert_ht(int key, int value, hash_t ht) {
    int idx;
    struct node_s *x = NULL;
    if(ht == NULL) {
        return;
    }

    idx = hash_func(key, ht->n);
    x = newNode(key, value, ht->elems[idx]);
    ht->elems[idx] = x;
}

int search_ht(int key, int *value, hash_t ht) {
    int idx;
    struct node_s *x = NULL;
    if (ht == NULL) {
        return -1;
    }

    idx = hash_func(key, ht->n);
    x = ht->elems[idx];

    while (x) {
        if (x->key == key) {
            *value = x->value;
            return 1;
        }
        x = x->next;
    }
    return 0;
}

void free_ht(hash_t ht) {
    int i;
    if (ht == NULL) {
        return;
    }

    for (i = 0; i < ht->n; i++) {
        struct node_s *current = ht->elems[i];
        while (current) {
            struct node_s *tmp = current;
            current = current->next;
            free(tmp);
        }
    }
    free(ht->elems);
    free(ht);
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    hash_t ht = hash_table_init(numsSize);
    int i, complement, idx, *res;

    for(i = 0; i < numsSize; i++) {
        complement = target - nums[i];
        if (search_ht(complement, &idx, ht)) {
            res = calloc(2, sizeof(int));
            res[0] = idx;
            res[1] = i;
            *returnSize = 2;
            free_ht(ht);
            return res;
        } 
        insert_ht(nums[i], i, ht);
    }
    free_ht(ht);
    *returnSize = 0;
    return NULL;
}
