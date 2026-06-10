/**
 * Problem:
 * Koko loves to eat bananas. There are n piles of bananas, the ith pile has
 * piles[i] bananas. The guards have gone and will come back in h hours.
 *
 * Koko can decide her bananas-per-hour eating speed of k. Each hour, she
 * chooses some pile of bananas and eats k bananas from that pile. If the pile
 * has less than k bananas, she eats all of them instead and will not eat any
 * more bananas during this hour.
 *
 * Koko likes to eat slowly but still wants to finish eating all the bananas
 * before the guards return.
 *
 * Return the minimum integer k such that she can eat all the bananas within h
 * hours.
 *
 * Solution:
 * We are asked to find the minimum eating speed k such that Koko can finish
 * all piles within h hours.
 *
 * Key observations:
 * 1. For a fixed k, we can compute how many hours Koko needs.
 *    Each pile of size p requires ceil(p / k) hours, because she eats at most
 *    k bananas per hour and any remainder takes an extra hour.
 *    We compute this efficiently as: (p + k - 1) / k.
 *
 * 2. The function hours_required(k) is monotonic:
 *    - If k is small -> hours are large
 *    - If k increases -> hours decrease
 *    This creates a pattern like:
 *        false false false true true true
 *    where "true" means hours_required(k) <= h.
 *
 * 3. Because of this monotonicity, we can apply binary search on k.
 *    The search space is:
 *        k ∈ [1, max(piles)]
 *
 * 4. We use a lower_bound-style binary search to find the smallest k
 *    such that hours_required(k) <= h:
 *      - If mid is too slow (hours > h), discard left half:
 *            l = mid + 1
 *      - Otherwise, mid is valid, so keep it and search left:
 *            r = mid
 *
 * 5. The loop maintains the invariant that the answer is always in [l, r].
 *    When the loop ends (l == r), we have the minimum valid k.
 *
 * Time Complexity: O(n log M) where n = pilesSize and M = max(piles)
 * Space Complexity: O(1)
 */
#include <stdlib.h>

int max(int *arr, int size)
{
    int max = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

int hours_required(int *piles, int pilesSize, int k)
{
    int hours = 0;

    for (int i = 0; i < pilesSize; i++) {
        hours += (piles[i] + k - 1) / k;
    }

    return hours;
}

int minEatingSpeed(int *piles, int pilesSize, int h)
{
    int l = 1, r = max(piles, pilesSize), mid;

    while (l < r) {
        mid = (r + l) / 2;

        if (hours_required(piles, pilesSize, mid) > h) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }

    return l;
}

int main(void)
{
    int piles[] = {3, 6, 7, 11};
    int k = minEatingSpeed(piles, 4, 8);
    return EXIT_SUCCESS;
}
