/**
 * Problem:
 * Given an integer array nums that may contain duplicates, return all possible
 * subsets (the power set).
 *
 * The solution set must not contain duplicate subsets. Return the solution in
 * any order.
 *
 * Solution:
 * Combination-style backtracking — sort first so duplicates are adjacent,
 * then at each call record the current subset and iterate from start to n-1
 * to extend it. Recording happens at every call (not just at a base case)
 * since every prefix accumulated so far is a valid subset, including the
 * empty one on the first call.
 *
 * Duplicate subsets are avoided by skipping any element at the same
 * recursion level that has the same value as the previous one
 * (i > start && nums[i] == nums[i-1]). The i > start guard ensures only
 * duplicate siblings at the same depth are skipped — the first pick at each
 * level is always taken. Without sorting this wouldn't work since duplicates
 * must be adjacent for the comparison to be meaningful.
 *
 * The solution array is pre-allocated to 2^n (worst case, no duplicates)
 * and shrunk via realloc after the recursion completes.
 *
 * Time Complexity:  O(n * 2^n) — up to 2^n subsets each copied in O(n).
 * Space Complexity: O(n * 2^n) — output storage; O(n) for subset buffer
 *                   and recursion call stack depth.
 */
#include <math.h>
#include <stdlib.h>

struct ctx_s {
    int **sol;
    int sol_idx;
    int *col_sizes;
};

void powerset(int *nums,
              int n,
              int *subset,
              int size,
              int start,
              struct ctx_s *ctx)
{

    ctx->sol[ctx->sol_idx] = calloc(size, sizeof(int));
    ctx->col_sizes[ctx->sol_idx] = size;
    for (int i = 0; i < size; i++) {
        ctx->sol[ctx->sol_idx][i] = subset[i];
    }
    ctx->sol_idx++;

    for (int i = start; i < n; i++) {
        if (i > start && nums[i] == nums[i - 1]) {
            continue;
        }
        subset[size] = nums[i];
        powerset(nums, n, subset, size + 1, i + 1, ctx);
    }
}

int cmp(const void *a, const void *b)
{
    return (*(int *)a) - (*(int *)b);
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume
 * caller calls free().
 */
int **subsetsWithDup(int *nums,
                     int numsSize,
                     int *returnSize,
                     int **returnColumnSizes)
{
    /*
     * With powerset we can have max 2^n solutions. Avoiding duplicated
     * solutions results in a smaller solution space. We can strip later
     * (realloc) unused space.
     */
    int sol_size = pow(2, numsSize);
    struct ctx_s ctx;
    ctx.sol = calloc(sol_size, sizeof(int *)),
    ctx.col_sizes = calloc(sol_size, sizeof(int));
    ctx.sol_idx = 0;
    int subset[numsSize];

    qsort(nums, numsSize, sizeof(int), cmp);
    powerset(nums, numsSize, subset, 0, 0, &ctx);

    if (ctx.sol_idx > 0) {
        ctx.sol = realloc(ctx.sol, ctx.sol_idx * sizeof(int *));
        ctx.col_sizes = realloc(ctx.col_sizes, ctx.sol_idx * sizeof(int));
    }

    *returnSize = ctx.sol_idx;
    *returnColumnSizes = ctx.col_sizes;

    return ctx.sol;
}

int main(void)
{
    int nums[3] = {1, 2, 2};
    int *ret_col_sizes = NULL;
    int sol_size;
    int **ret = subsetsWithDup(nums, 3, &sol_size, &ret_col_sizes);
    return EXIT_SUCCESS;
}
