/*
 * Problem:
 * Given an integer array nums, return true if any value 
 * appears at least twice in the array, and return false 
 * if every element is distinct.
 *
 * Solution:
 * Sorted array in ascending order using qsort. Once sorted
 * check if the adjacent number (i-1) is the same and return immediately.
 *
 * Time complexity: O(n * log n)
 * Space complexity: O(1)
 */

int compare(const void *num1, const void *num2) {
    int a = *(int *)num1;
    int b = *(int *)num2;

    return (a > b) - (a < b);
}

bool containsDuplicate(int* nums, int numsSize) {
    int i;
    qsort(nums, numsSize, sizeof(int), compare);

    for (i = 1; i < numsSize; i++) {
        if (nums[i] == nums[i - 1]) {
            return true;
        }
    }
    return false;
}
