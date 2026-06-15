/**
 * Problem:
 * Given an array of integers nums containing n + 1 integers where each integer
 * is in the range [1, n] inclusive.
 * There is only one repeated number in nums, return this repeated number.
 * You must solve the problem without modifying the array nums and using only 
 * constant extra space.
 *
 * Solution:
 * For each element, use its absolute value as an index and negate the
 * element at that index to mark it as visited. If the element at that
 * index is already negative, the index has been visited twice, meaning
 * the current value is the duplicate.
 *  
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
#include <stdlib.h>

int findDuplicate(int *nums, int numsSize)
{
    for (int i = 0; i < numsSize; i++) {
        if (nums[abs(nums[i]) - 1] < 0) {
            return abs(nums[i]);
        } else {
            nums[abs(nums[i]) - 1] *= -1;
        }
    }
    return -1;
}

int main(void)
{
    int nums[5] = {1, 3, 4, 2, 2};
    int res = findDuplicate(nums, 5);
    return EXIT_SUCCESS;
}
