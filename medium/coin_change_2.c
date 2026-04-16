#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * We are given:
 *   - A list of coins
 *   - A target amount
 * We must compute:
 *   - How many different ways we can make that amount.
 *
 * We are asked to COUNT the number of combinations to form a sum.
 *
 * 1. Does the order matter?
 *   - For coin change problems, order does NOT matter
 *     (e.g., [2,1,2] is the same as [1,2,2]).
 *   - Therefore this is NOT a permutation problem.
 *
 * 2. Is subset size fixed?
 *   - Are we choosing exactly K coins? No. The number of coins used depends
 *     on how we reach the target.
 *   - Therefore this is NOT a fixed-size combination problem.
 *
 * 3. Are we allowed to use the same coin multiple times?
 *   - Yes (e.g., using coing 1 five times to make 5)
 *   - This immediately classifies the problem as
 *     "combination with repetitions"!
 *
 * 4. Why it is NOT a power set?
 *   - Power set problems:
 *     - ask for all subsets
 *     - do not usaully involve sum contraints
 *     - every element is included or excluded once
 *   - Here:
 *     - elements can be used multiple times
 *     - we are building sums
 *     - we are not simply including/excluding once
 *
 * ----> BACKTRACKING could be a solution.
 * The problem naturally forms a decision tree:
 *
 * At each step:
 *   - choose a coin
 *   - subtract its value from the remaining target
 *   - continue building the solution
 *
 * We stop when:
 *   - target = 0 -> valid combination found
 *   - target < 0 -> invalid path, prune
 *
 * This is a classic DFS over combinations.
 *
 * Time complexity = O(2^n) -> exponential
 * Space complexity = O(n)
 *
 * Backtracking is good when n is small and we are asked to return the actual
 * combinations. The best solution here is to use dynamic programming (DP)!
 *
 * DP can be divided in top-down (memoization) and bottom-up (tabulation).
 *
 * In the first case, we keep the solution recursive and add a memoization
 * table to avoid repeated calls of same subproblems.
 *
 * In the second case, start with the smallest subproblems and gradually build
 * up to the final solution. (iterative solution -> no recursion).
 *
 */

/* Backtracking solution: not good for large n */
void comb_rep(int target,
              int *candidates,
              int n,
              int start,
              int *current,
              int current_size,
              int *sol)
{
    if (target == 0) {
        (*sol)++;
        return;
    }

    if (target < 0) {
        return;
    }

    for (int i = start; i < n; i++) {
        current[current_size] = candidates[i];

        comb_rep(target - candidates[i],
                 candidates,
                 n,
                 i, // maintain the same index
                 current,
                 current_size + 1,
                 sol);
    }
}

int change(int amount, int *coins, int coinsSize)
{
    int sol = 0;
    int *current = calloc(amount, sizeof(int));
    comb_rep(amount, coins, coinsSize, 0, current, 0, &sol);
    free(current);
    return sol;
}

/*
 * DP solution (1-D DP)
 *
 * When to Use 1-D DP?
 *
 * A problem is suitable for 1D DP if it exhibits:
 *   - Optimal Substructure: An optimal solution contains optimal solutions to
 *     subproblems.
 *   - Overlapping Subproblems: The same subproblems are solved repeatedly.
 *
 * The Three Pillars of 1D DP:
 *   - Pillar 1: Optimization Problems
 *     Goal: Find the best (min/max) value under constraints.
 *
 *   - Pillar 2: Counting Problems
 *     Goal: Count the number of ways to achieve a condition.
 *
 *   - Pillar 3: Sequential Decision-Making
 *     Goal: Make a series of choices where each decision affects future
 *     options.
 */

int change_v2(int amount, int *coins, int coinsSize)
{
    /*
     * Define a DP array where dp[i] represents the number of ways to form
     * the sum 'i'. It has to be of size amount + 1 to include also number 0.
     */
    uint32_t *dp = calloc(amount + 1, sizeof(uint32_t));
    int i, j, res;

    dp[0] = 1; // only 1 solution to form 0 (choose nothing from coins[])

    for (i = 0; i < coinsSize; i++) {
        for (j = coins[i]; j <= amount; j++) {
            dp[j] += dp[j - coins[i]];
        }
    }

    res = dp[amount];
    free(dp);
    return res;
}

int main(void)
{
    int coins[3] = {1, 2, 5};
    int amount = 5;

    int combinations = change_v2(amount, coins, 3);
    printf("The possible ways to make the amount are: %d\n", combinations);
    return 0;
}
