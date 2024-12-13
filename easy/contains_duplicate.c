/* HashSet */
struct node_s {
    int value;
    struct node_s *next;
};

struct hashset_s {
    struct node_s **buckets;
    int size;
};

int hash(int key, int size) {
    return abs(key) % size;
}

struct hashset_s *hashset_init(int size) {
    struct hashset_s *x = calloc(1, sizeof(struct hashset_s));
    x->buckets = calloc(size, sizeof(struct node_s *));
    x->size = size;
    return x;
}

struct node_s *newNode(int value, struct node_s *next) {
    struct node_s *x = calloc(1, sizeof(struct node_s));
    x->value = value;
    x->next = next;
    return x;
}

bool hashset_add(struct hashset_s *hs, int value) {
    int idx = hash(value, hs->size);
    struct node_s *current = hs->buckets[idx];

    while (current != NULL) {
        if(current->value == value) return true;
        current = current->next;
    }

    hs->buckets[idx] = newNode(value, hs->buckets[idx]);
    return false;
}

void hashset_free(struct hashset_s *hs) {
    for (int i = 0; i < hs->size; i++) {
        struct node_s *current = hs->buckets[i];
        while (current != NULL) {
            struct node_s *temp = current;
            current = current->next;
            free(temp);
        }
    }

    free(hs->buckets);
    free(hs);
}

bool containsDuplicate(int* nums, int numsSize) {
    struct hashset_s *hs = hashset_init(numsSize);
    for (int i = 0; i < numsSize; i++) {
        if (hashset_add(hs, nums[i])) return true;
    }
    
    hashset_free(hs);
    return false;
}
