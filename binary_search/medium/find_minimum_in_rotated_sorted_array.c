/**
 * Problem:
 * Suppose an array of length n sorted in ascending order is rotated between 1
 * and n times. For example, the array nums = [0,1,2,4,5,6,7] might become:
 *   [4,5,6,7,0,1,2] if it was rotated 4 times.
 *   [0,1,2,4,5,6,7] if it was rotated 7 times.
 * Notice that rotating an array [a[0], a[1], a[2], ..., a[n-1]] 1 time results
 * in the array [a[n-1], a[0], a[1], a[2], ..., a[n-2]].
 *
 * Given the sorted rotated array nums of unique elements, return the minimum
 * element of this array.
 *
 * You must write an algorithm that runs in O(log n) time.
 *
 * Solution:
 * We use binary search to locate the rotation pivot (the smallest element).
 * In a rotated sorted array, values are split into two parts:
 * - left part: elements >= nums[0]
 * - right part: elements < nums[0] (contains the minimum)
 *
 * At each step:
 * - if nums[mid] >= nums[0], we are in the left part -> move right
 *   (l = mid + 1)
 * - otherwise, we are in the right part -> move left (r = mid)
 *
 * The loop finds the first element smaller than nums[0], which is the minimum.
 * If the array is not rotated, l becomes numsSize, so we return nums[l %
 * numsSize] to wrap around to index 0.
 *
 * Time Complexity: O(log n)
 * Space Complexity: O(1)
 */
#include <stdlib.h>

int findMin(int *nums, int numsSize)
{
    int l = 0, r = numsSize, mid;

    while (l < r) {
        mid = (l + r) / 2;

        if (nums[mid] >= nums[0]) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }

    return nums[l % numsSize];
}

int main(void)
{
    int nums[] = {14, 5, 6, 7, 0, 1, 2};
    int min = findMin(nums, 7);
    return EXIT_SUCCESS;
}
