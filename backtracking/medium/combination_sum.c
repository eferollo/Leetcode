/**
 * Problem:
 * Given an array of distinct integers candidates and a target integer target,
 * return a list of all unique combinations of candidates where the chosen
 * numbers sum to target. You may return the combinations in any order.
 *
 * The same number may be chosen from candidates an unlimited number of times.
 * Two combinations are unique if the frequency of at least one of the chosen
 * numbers is different.
 *
 * The test cases are generated such that the number of unique combinations
 * that sum up to target is less than 150 combinations for the given input.
 *
 * Solution:
 * Backtracking with a running sum. At each call, iterate candidates from
 * start to n-1, appending candidates[i] to the current subset and recursing
 * with sum + candidates[i] and start = i (not i+1) — keeping start at i
 * allows the same candidate to be picked again in deeper calls, implementing
 * unlimited reuse. Two pruning conditions terminate branches early: if sum
 * exceeds target the branch is abandoned; if sum equals target the current
 * subset is copied into the solution. Iterating from start (not 0) avoids
 * generating permutations of the same combination, ensuring uniqueness.
 *
 * Time Complexity:  O(n^(t/m)) where t is target and m is the smallest
 *                   candidate — the maximum recursion depth is t/m and each
 *                   level branches up to n ways.
 * Space Complexity: O(t/m) for the subset buffer and call stack depth;
 *                   O(k * t/m) for the output where k is the number of valid
 *                   combinations.
 */
#include <stdbool.h>
#include <stdlib.h>

struct ctx_s {
    int **sol;
    int sol_idx;
    int *col_sizes;
    int capacity;
};

void rep_comb(int *nums,
              int n,
              int pos,
              int *subset,
              int size,
              int target,
              int start,
              int sum,
              struct ctx_s *ctx)
{
    if (sum > target) {
        return;
    }

    if (sum == target) {
        if (ctx->sol_idx == ctx->capacity) {
            ctx->capacity *= 2;
            ctx->sol = realloc(ctx->sol, ctx->capacity * sizeof(int *));
            ctx->col_sizes =
                realloc(ctx->col_sizes, ctx->capacity * sizeof(int));
        }
        ctx->col_sizes[ctx->sol_idx] = size;
        ctx->sol[ctx->sol_idx] = calloc(size, sizeof(int));
        for (int i = 0; i < size; i++) {
            ctx->sol[ctx->sol_idx][i] = nums[subset[i]];
        }
        ctx->sol_idx++;
        return;
    }

    for (int i = start; i < n; i++) {
        subset[pos] = i;
        rep_comb(nums,
                 n,
                 pos + 1,
                 subset,
                 size + 1,
                 target,
                 i,
                 sum + nums[i],
                 ctx);
    }
    return;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume
 * caller calls free().
 */
int **combinationSum(int *candidates,
                     int candidatesSize,
                     int target,
                     int *returnSize,
                     int **returnColumnSizes)
{
    struct ctx_s ctx;
    ctx.capacity = 2;
    ctx.sol = calloc(ctx.capacity, sizeof(int *));
    ctx.sol_idx = 0;
    ctx.col_sizes = calloc(ctx.capacity, sizeof(int));
    int subset[target];

    rep_comb(candidates, candidatesSize, 0, subset, 0, target, 0, 0, &ctx);

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
    int candidates[] = {2, 3, 6, 7};
    int *ret_col_size = NULL;
    int ret_size = 0;
    int **ret = combinationSum(candidates, 4, 7, &ret_size, &ret_col_size);
    return EXIT_SUCCESS;
}
