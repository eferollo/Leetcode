/**
 * Problem:
 * Given an array nums of distinct integers, return all the possible
 * permutations. You can return the answer in any order.
 *
 * Solution:
 * Backtracking with a mark array to track which elements have been used in
 * the current permutation. At each position pos, try every unmarked element,
 * mark it, recurse to fill pos + 1, then unmark it (backtrack) so it can be
 * reused in other branches. When pos == n all positions are filled and the
 * current subset (stored as indices into nums) is copied into the solution.
 *
 * Since the number of permutations is exactly n!, the solution array is
 * pre-allocated to n! rows with each row pre-allocated to n elements,
 * avoiding any reallocation during recursion.
 *
 * Time Complexity:  O(n * n!) — n! permutations each of length n to copy.
 * Space Complexity: O(n * n!) — output storage; O(n) for the mark array,
 *                   subset buffer, and recursion call stack depth.
 */
#include <stdlib.h>

struct ctx_s {
    int **sol;
    int sol_idx;
    int *col_sizes;
};

unsigned long long factorial(int n)
{
    unsigned long long result = 1;

    for (int i = 2; i <= n; i++) {
        result *= i;
    }

    return result;
}

void simple_perm(int *nums,
                 int n,
                 int pos,
                 int *subset,
                 int *mark,
                 struct ctx_s *ctx)
{
    if (pos >= n) {
        for (int i = 0; i < n; i++) {
            ctx->sol[ctx->sol_idx][i] = nums[subset[i]];
        }
        ctx->sol_idx++;
        return;
    }

    for (int i = 0; i < n; i++) {
        if (mark[i] == 0) {
            mark[i] = 1;
            subset[pos] = i;
            simple_perm(nums, n, pos + 1, subset, mark, ctx);
            mark[i] = 0;
        }
    }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume
 * caller calls free().
 */
int **permute(int *nums, int numsSize, int *returnSize, int **returnColumnSizes)
{
    struct ctx_s ctx;
    int sol_size = factorial(numsSize);
    int *mark = calloc(numsSize, sizeof(int));
    int subset[numsSize];

    ctx.col_sizes = calloc(sol_size, sizeof(int));
    ctx.sol = calloc(sol_size, sizeof(int *));
    ctx.sol_idx = 0;
    for (int i = 0; i < sol_size; i++) {
        ctx.sol[i] = calloc(numsSize, sizeof(int));
        ctx.col_sizes[i] = numsSize;
    }

    simple_perm(nums, numsSize, 0, subset, mark, &ctx);

    *returnColumnSizes = ctx.col_sizes;
    *returnSize = sol_size;
    free(mark);
    return ctx.sol;
}

int main(void)
{
    int nums[] = {1, 2, 3};
    int *col_sizes;
    int size = 0;
    int **res = permute(nums, 3, &size, &col_sizes);
    return EXIT_SUCCESS;
}
