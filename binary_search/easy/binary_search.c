/**
 * Problem:
 * Given an array of integers nums which is sorted in ascending order, and an 
 * integer target, write a function to search target in nums. If target exists, 
 * then return its index. Otherwise, return -1. 
 *
 * You must write an algorithm with O(log n) runtime complexity.
 *
 * Solution:
 * Binary search!
 *
 * Time Complexity: O(log n)
 * Space Complexity: O(1)
 */
#include <stdlib.h>

int search(int *nums, int numsSize, int target)
{
    int l = 0, r = numsSize - 1, mid;
    while (l <= r) {
        mid = l + (r - l) / 2;

        if (nums[mid] == target) {
            return mid;
        }

        if (nums[mid] < target) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return -1;
}

int main(void)
{
    int nums[] = {-1, 0, 3, 5, 9, 12};
    int i = search(nums, 6, 9);
    return EXIT_SUCCESS;
}
