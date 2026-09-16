/**
 * Problem:
 * Given an integer array nums of unique elements, return all possible subsets
 * (the power set).
 * The solution set must not contain duplicate subsets. Return the solution in
 * any order.
 *
 * Solution:
 * Recursive backtracking with an include/exclude decision at each position.
 * At each call, two branches are taken for nums[pos]: exclude it (recurse
 * with the same subset and size) or include it (append it to subset, recurse
 * with size + 1). When pos == n all elements have been decided — copy the
 * current subset into the solution array and advance sol_idx.
 *
 * Since every element is either included or excluded independently, the
 * recursion produces exactly 2^n leaves, one per subset. The solution array
 * is pre-allocated to 2^n rows so no reallocation is needed during recursion.
 *
 * Time Complexity:  O(n * 2^n) — 2^n subsets, each copied in O(n) worst case.
 * Space Complexity: O(n * 2^n) — output storage; O(n) for the subset buffer
 *                   and recursion call stack depth.
 */
#include <math.h>
#include <stdlib.h>

void powerset(int *nums,
              int n,
              int pos,
              int *subset,
              int size,
              int ***sol,
              int *sol_idx,
              int **ret_col_sizes)
{
    if (pos == n) {
        (*sol)[*sol_idx] = calloc(size, sizeof(int));
        (*ret_col_sizes)[*sol_idx] = size;
        for (int i = 0; i < size; i++) {
            (*sol)[*sol_idx][i] = subset[i];
        }
        (*sol_idx)++;
        return;
    }

    /* Don't take nums[pos] */
    powerset(nums, n, pos + 1, subset, size, sol, sol_idx, ret_col_sizes);

    /* Take nums[pos] */
    subset[size] = nums[pos];
    powerset(nums, n, pos + 1, subset, size + 1, sol, sol_idx, ret_col_sizes);
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume
 * caller calls free().
 */
int **subsets(int *nums, int numsSize, int *returnSize, int **returnColumnSizes)
{
    int sol_size = (int)pow(2, numsSize);
    int **sol = calloc(sol_size, sizeof(int *));
    *returnColumnSizes = calloc(sol_size, sizeof(int));

    int subset[numsSize];
    int sol_idx = 0;
    powerset(nums, numsSize, 0, subset, 0, &sol, &sol_idx, returnColumnSizes);
    *returnSize = sol_size;

    return sol;
}

int main(void)
{
    int nums[3] = {1, 2, 3};
    int *ret_col_sizes = NULL;
    int sol_size;
    int **ret = subsets(nums, 3, &sol_size, &ret_col_sizes);
    return EXIT_SUCCESS;
}
