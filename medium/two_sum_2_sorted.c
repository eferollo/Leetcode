/**
 * Given a 1-indexed array of integers numbers that is already sorted in
 * non-decreasing order, find two numbers such that they add up to a specific
 * target number. Let these two numbers be numbers[index1] and numbers[index2]
 * where 1 <= index1 < index2 <= numbers.length.
 *
 * Return the indices of the two numbers index1 and index2, each incremented
 * by one, as an integer array [index1, index2] of length 2. The tests are
 * generated such that there is exactly one solution. You may not use the same
 * element twice.
 *
 * Your solution must use only constant extra space.
 *
 * Solution:
 * We iterate through the array and, for each element, search for its
 * complement (target - numbers[i]) in the remaining portion of the array
 * using binary search. The search starts from index i + 1 to avoid reusing
 * the same element.
 *
 * Time Complexity: O(n log n)
 * Space Complexity: O(1)
 */
#include <stdlib.h>

int binary_search(int *n, int size, int target, int l)
{
    int left = l, right = size - 1, mid;

    while (left <= right) {
        mid = left + (right - left) / 2;
        if (n[mid] == target) {
            return mid;
        }
        if (n[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *twoSum(int *numbers, int numbersSize, int target, int *returnSize)
{
    int i, found = -1;
    int *res = calloc(2, sizeof(int));
    *returnSize = 2;

    for (i = 0; i < numbersSize; i++) {
        found = binary_search(numbers, numbersSize, target - numbers[i], i + 1);
        if (found != -1) {
            res[0] = i + 1;
            res[1] = found + 1;
            return res;
        }
    }
    return res;
}

int main(void)
{
    int numbers[] = {-1, 0};
    int size = 0;
    int *res = twoSum(numbers, 2, -1, &size);
    return EXIT_SUCCESS;
}
