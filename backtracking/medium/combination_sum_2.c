/**
 * Problem:
 * Given a collection of candidate numbers (candidates) and a target number
 * (target), find all unique combinations in candidates where the candidate
 * numbers sum to target. Each number in candidates may only be used once in the
 * combination.
 *
 * Note: The solution set must not contain duplicate combinations.
 *
 * Solution:
 * Same backtracking approach as combinationSum but with two key differences:
 *
 * 1. Each candidate may only be used once — pass start = i + 1 (not i) in
 *    the recursive call so the next level only considers candidates after the
 *    current index.
 *
 * 2. Duplicate candidates must not produce duplicate combinations — sort the
 *    candidates first so duplicates are adjacent, then skip any candidate at
 *    the same recursion level that has the same value as the previous one
 *    (i > start && nums[i] == nums[i-1]). The i > start guard ensures only
 *    sibling picks at the same depth are skipped, not the first pick at that
 *    level, which is always valid.
 *
 * Running sum prunes branches early: abandon if sum > target, record if sum
 * == target, continue picking otherwise.
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

void simple_comb(int *nums,
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
        if (i > start && nums[i] == nums[i - 1]) {
            continue;
        }
        subset[pos] = i;
        simple_comb(nums,
                    n,
                    pos + 1,
                    subset,
                    size + 1,
                    target,
                    i + 1,
                    sum + nums[i],
                    ctx);
    }
    return;
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
int **combinationSum2(int *candidates,
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

    qsort(candidates, candidatesSize, sizeof(int), cmp);
    simple_comb(candidates, candidatesSize, 0, subset, 0, target, 0, 0, &ctx);

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
    int **ret = combinationSum2(candidates, 4, 7, &ret_size, &ret_col_size);
    return EXIT_SUCCESS;
}
