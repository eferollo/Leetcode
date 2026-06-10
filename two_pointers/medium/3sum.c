/**
 * Given an integer array nums, return all the triplets
 * [nums[i], nums[j], nums[k]] such that i != j, i != k, and j != k, and
 * nums[i] + nums[j] + nums[k] == 0.
 *
 * Notice that the solution set must not contain duplicate triplets.
 *
 * Example 1:
 * Input: nums = [-1,0,1,2,-1,-4]
 * Output: [[-1,-1,2],[-1,0,1]]
 * Explanation:
 * nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0.
 * nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0.
 * nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0.
 * The distinct triplets are [-1,0,1] and [-1,-1,2].
 * Notice that the order of the output and the order of the triplets does not
 * matter.
 *
 * Solution:
 * We first sort the array to enable the two-pointer technique and easy
 * duplicate handling. Then, for each element nums[i], we fix it as the
 * first value and use two pointers (j = i+1, k = end) to find pairs
 * such that nums[i] + nums[j] + nums[k] == 0.
 *
 * If the sum is too large, we move k left; if too small, we move j right.
 * When a valid triplet is found, we store it, skip duplicates for j,
 * and continue searching.
 *
 * We also skip duplicate values for i to avoid repeated triplets.
 * The result array is dynamically resized as needed.
 *
 * Avoiding duplicates:
 *
 * 1. For the first element (i):
 *    Since the array is sorted, equal values are adjacent.
 *    We skip nums[i] if it's the same as the previous one:
 *        if (i > 0 && nums[i] == nums[i - 1]) continue;
 *    This prevents generating triplets starting with the same value.
 *
 * 2. For the second element (j):
 *    After finding a valid triplet, we increment j and skip all
 *    consecutive duplicates:
 *        while (j < k && nums[j] == nums[j - 1]) j++;
 *    This ensures we don’t repeat the same pair (nums[i], nums[j]).
 *
 * 3. For the third element (k):
 *    We don’t explicitly skip duplicates for k because adjusting j
 *    and skipping its duplicates is sufficient to avoid repeating
 *    the same triplet in this pattern.
 *
 * Key idea:
 * Sorting groups duplicates together, so we can skip them in-place
 * and ensure each unique triplet is added only once.
 *
 * Time Complexity: O(n^2)
 * Space Complexity: O(1)
 */
#include <stdlib.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume
 * caller calls free().
 */

int compare(const void *a, const void *b)
{
    return (*(int *)a) - (*(int *)b);
}

int **
threeSum(int *nums, int numsSize, int *returnSize, int **returnColumnSizes)
{
    size_t capacity = 4, found = 0;
    int **res = calloc(capacity, sizeof(int *));
    *returnColumnSizes = calloc(capacity, sizeof(int));
    // free if fail

    int i, j, k, sum;
    qsort(nums, numsSize, sizeof(int), compare);

    for (i = 0; i < numsSize; i++) {
        if (i > 0 && nums[i] == nums[i - 1]) {
            continue;
        }

        j = i + 1;
        k = numsSize - 1;
        while (j < k) {
            sum = nums[i] + nums[j] + nums[k];
            if (sum > 0) {
                /* The array is sorted, decrease upper bound */
                k--;
            } else if (sum < 0) {
                /* Increase lower bound */
                j++;
            } else {
                if (found >= capacity) {
                    capacity *= 2;
                    res = realloc(res, capacity * sizeof(int *));
                    *returnColumnSizes =
                        realloc(*returnColumnSizes, capacity * sizeof(int));
                    // free if fail (use tmp)
                }

                res[found] = calloc(3, sizeof(int));
                // free if fail
                res[found][0] = nums[i];
                res[found][1] = nums[j];
                res[found][2] = nums[k];

                (*returnColumnSizes)[found] = 3;
                found++;
                j++;

                /* Remove duplicates for the second element */
                while (j < k && nums[j] == nums[j - 1]) {
                    j++;
                }
            }
        }
    }
    *returnSize = found;
    return res;
}

int main(void)
{
    int nums[] = {-1, 0, 1, 2, -1, -4};
    int size = 0;
    int *cols;
    int **res = threeSum(nums, 5, &size, &cols);
    return EXIT_SUCCESS;
}
