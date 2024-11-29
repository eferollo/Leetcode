int find(int *parent, int i) {
    if(parent[i] != i) {
        /* Path compression */
        parent[i] = find(parent, parent[i]);
    }
    return parent[i];
}

void union_sets(int *parent, int i, int j) {
    parent[find(parent, i)] = find(parent, j);
}

bool validPath(int n, int** edges, int edgesSize, int* edgesColSize, int source, int destination) {
    int *parent = NULL, i;

    parent = calloc(n, sizeof(int));
    for (i = 0; i < n; i++) {
        parent[i] = i;
    }

    for (i = 0; i < edgesSize; i++) {
        union_sets(parent, edges[i][0], edges[i][1]);
    }

    bool res = find(parent, source) == find(parent, destination);

    free(parent);
    return res;    
}
