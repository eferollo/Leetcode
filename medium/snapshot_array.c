typedef struct {
    int snap_id;
    int value;
} SnapPair;

typedef struct {
    SnapPair *snaps;
    int size;
    int capacity;
} SnapList;

typedef struct {
    SnapList *arr;
    int length;
    int snap_id;
} SnapshotArray;

SnapList *snap_list_init() {
    SnapList *x = calloc(1, sizeof(SnapList));
    x->size = 0;
    x->capacity = 2;
    x->snaps = calloc(x->capacity, sizeof(SnapPair));

    return x;
}

void snap_list_add(SnapList *list, int snap_id, int value) {
    if (list->size > 0 && list->snaps[list->size - 1].snap_id == snap_id) {
        list->snaps[list->size - 1].value = value;
        return;
    }

    if (list->size >= list->capacity) {
        list->capacity *= 2;
        list->snaps = realloc(list->snaps, list->capacity * sizeof(SnapPair));
    }

    list->snaps[list->size].snap_id = snap_id;
    list->snaps[list->size].value = value;
    list->size++;
}

int snap_list_get(SnapList *list, int snap_id) {
    int left = 0, right = list->size - 1, mid;

    /* Binary search. Take the value equal to the equal or 
    most recent snap_id */
    while(left <= right) {
        mid = left + (right - left) / 2;
        if (list->snaps[mid].snap_id <= snap_id) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return list->snaps[right].value;
}

SnapshotArray* snapshotArrayCreate(int length) {
    int i;
    SnapshotArray *x = calloc(1, sizeof(SnapshotArray));
    x->length = length;
    x->arr = calloc(length, sizeof(SnapList));
    x->snap_id = 0;

    for (i = 0; i < length; i++) {
        x->arr[i] = *snap_list_init();
        snap_list_add(&x->arr[i], 0, 0);
    }
    return x; 
}

void snapshotArraySet(SnapshotArray* obj, int index, int val) {
    snap_list_add(&obj->arr[index], obj->snap_id, val);
}

int snapshotArraySnap(SnapshotArray* obj) {
    return obj->snap_id++;
}

int snapshotArrayGet(SnapshotArray* obj, int index, int snap_id) {
    return snap_list_get(&obj->arr[index], snap_id);
}

void snapshotArrayFree(SnapshotArray* obj) {
    int i;
    for (i = 0; i < obj->length; i++) {
        free(obj->arr[i].snaps);
    }
    free(obj->arr);
    free(obj);
}

/**
 * Your SnapshotArray struct will be instantiated and called as such:
 * SnapshotArray* obj = snapshotArrayCreate(length);
 * snapshotArraySet(obj, index, val);
 
 * int param_2 = snapshotArraySnap(obj);
 
 * int param_3 = snapshotArrayGet(obj, index, snap_id);
 
 * snapshotArrayFree(obj);
*/
