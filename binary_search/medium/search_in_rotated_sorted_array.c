/**
 * Problem:
 * There is an integer array nums sorted in ascending order (with distinct
 * values).
 *
 * Prior to being passed to your function, nums is possibly left rotated at an
 * unknown index k (1 <= k < nums.length) such that the resulting array is
 * [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]]
 * (0-indexed). For example, [0,1,2,4,5,6,7] might be left rotated by 3 indices
 * and become [4,5,6,7,0,1,2].
 *
 * Given the array nums after the possible rotation and an integer target,
 * return the index of target if it is in nums, or -1 if it is not in nums.
 *
 * You must write an algorithm with O(log n) runtime complexity
 *
 * Solution:
 * We perform a modified binary search on a rotated sorted array.
 * At each step, one half of the array is always sorted.
 *
 * 1. Check which half is sorted:
 *    - If nums[l] <= nums[mid], the left half [l, mid] is sorted.
 *    - Otherwise, the right half [mid, r] is sorted.
 *
 * 2. Once we know the sorted half, we check if the target lies inside it:
 *
 *    - Left sorted case:
 *        if (nums[l] <= target && target <= nums[mid])
 *      This works because in a sorted range, values are continuous and ordered,
 *      so the target must be between the endpoints to be inside.
 *      If true -> discard right half (r = mid - 1)
 *      Else    -> discard left half (l = mid + 1)
 *
 *    - Right sorted case:
 *        if (nums[mid] <= target && target <= nums[r])
 *      Same reasoning: since this half is sorted, the target must fall within
 *      its boundary values to be there.
 *      If true -> discard left half (l = mid + 1)
 *      Else    -> discard right half (r = mid - 1)
 *
 * By always selecting the half where the target could exist and discarding
 * the other, we reduce the search space by half each iteration.
 *
 * Time Complexity: O(log n)
 * Space Complexity: O(1)
 */
#include <stdlib.h>

int search(int *nums, int numsSize, int target)
{
    int l = 0, r = numsSize - 1, mid;

    while (l <= r) {
        mid = (l + r) / 2;

        if (nums[mid] == target) {
            return mid;
        }

        if (nums[l] <= nums[mid]) {
            if (nums[l] <= target && target <= nums[mid]) {
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        } else {
            if (nums[mid] <= target && target <= nums[r]) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
    }

    return -1;
}

int main(void)
{
    int nums[] = {4, 5, 6, 7, 0, 1, 2};
    int res = search(nums, 7, 0);
    return EXIT_SUCCESS;
}
