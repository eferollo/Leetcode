/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

// O(n^2) O(n^2)
int** generate(int numRows, int* returnSize, int** returnColumnSizes) {
    int **res = NULL, i, j;

    res = calloc(numRows, sizeof(int *));
    int *sizes = calloc(numRows, sizeof(int));

    for (i = 0; i < numRows; i++) {
        res[i] = calloc(i+1, sizeof(int));
        if(i == 0) {
            res[i][0] = 1;
            sizes[i] = 1;
            continue;
        }
        for (j = 0; j <= i; j++) {
            if(j == 0 || j == i) {
                res[i][j] = 1;
            } else {
                res[i][j] = res[i-1][j-1] + res[i-1][j];
            }
        }
        sizes[i] = j;
    }
    *returnColumnSizes = sizes;
    *returnSize = numRows;
    return res;
}

// Binomial coefficient O(n^2) O(1)
int** generate(int numRows, int* returnSize, int** returnColumnSizes) {
    int **res = NULL, i, j;

    res = calloc(numRows, sizeof(int *));
    int *sizes = calloc(numRows, sizeof(int));

    for (i = 0; i < numRows; i++) {
        res[i] = calloc(i+1, sizeof(int));
        sizes[i] = i+1;

        for (j = 0; j <= i; j++) {
            if(j == 0 || j == i) {
                res[i][j] = 1;
            } else {
                res[i][j] = res[i][j-1] * (i-j+1) / j;
            }
        }
    }
    *returnColumnSizes = sizes;
    *returnSize = numRows;
    return res;
}
