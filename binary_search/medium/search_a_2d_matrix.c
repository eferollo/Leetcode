/**
 * Problem:
 * You are given an m x n integer matrix matrix with the following two
 * properties:
 *
 * Each row is sorted in non-decreasing order.
 * The first integer of each row is greater than the last integer of the
 * previous row.
 *
 * Given an integer target, return true if target is in matrix or false
 * otherwise.
 *
 * You must write a solution in O(log(m * n)) time complexity.
 *
 * Solution:
 * We treat the matrix as a flattened sorted array of size m * n, since
 * each row is sorted and every row's first element is greater than the
 * previous row's last. We then perform a standard binary search on the
 * virtual array.
 *
 * For a given index mid, we map it back to 2D coordinates using:
 * row = mid / n and col = mid % n, allowing us to access the element
 * in the original matrix without extra space.
 *
 * Time Complexity: O(log(m * n))
 * Space Complexity: O(1)
 */
#include <stdbool.h>
#include <stdlib.h>

bool searchMatrix(int **matrix, int matrixSize, int *matrixColSize, int target)
{
    int row, col;
    int col_size = matrixColSize[0];
    int len = matrixSize * col_size;
    int l = 0, r = len - 1, mid;

    while (l <= r) {
        mid = l + (r - l) / 2;
        row = mid / col_size;
        col = mid % col_size;

        if (matrix[row][col] == target) {
            return true;
        }

        if (matrix[row][col] < target) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    return false;
}

int main(void)
{
    int matrixSize = 3;

    int **matrix = malloc(matrixSize * sizeof(int *));
    matrix[0] = malloc(4 * sizeof(int));
    matrix[1] = malloc(4 * sizeof(int));
    matrix[2] = malloc(4 * sizeof(int));

    int row0[] = {1, 3, 5, 7};
    int row1[] = {10, 11, 16, 20};
    int row2[] = {23, 30, 34, 60};
    for (int i = 0; i < 4; i++) {
        matrix[0][i] = row0[i];
        matrix[1][i] = row1[i];
        matrix[2][i] = row2[i];
    }

    int *matrixColSize = malloc(matrixSize * sizeof(int));
    for (int i = 0; i < matrixSize; i++) {
        matrixColSize[i] = 4;
    }

    bool found = searchMatrix(matrix, matrixSize, matrixColSize, 3);
    return EXIT_SUCCESS;
}
