/**
 * Problem:
 * You are given an array prices where prices[i] is the price of a given stock
 * on the ith day.
 *
 * You want to maximize your profit by choosing a single day to buy one stock
 * and choosing a different day in the future to sell that stock.
 *
 * Return the maximum profit you can achieve from this transaction. If you
 * cannot achieve any profit, return 0.
 *
 * Solution:
 * We track the minimum price seen so far (best day to buy).
 * For each day, we compute the profit if we sell today:
 *   profit = current price - min
 * and update the maximum profit.
 *
 * This works because at each step we use the cheapest previous price
 * as the optimal buy.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
#include <stdlib.h>

int maxProfit(int *prices, int pricesSize)
{
    int i, max_profit = 0, profit;
    int min = prices[0];

    for (i = 1; i < pricesSize; i++) {
        if (prices[i] < min) {
            min = prices[i];
        }

        profit = prices[i] - min;
        if (profit > max_profit) {
            max_profit = profit;
        }
    }

    return max_profit;
}

int main(void)
{
    int prices[] = {7, 1, 5, 3, 6, 4};
    int res = maxProfit(prices, 6);
    return EXIT_SUCCESS;
}
