/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sortedSquares(int* nums, int numsSize, int* returnSize) {
    int i, *res = NULL;
    int left = 0, right = numsSize - 1;
    int pos = numsSize - 1;

    res = calloc(numsSize, sizeof(int));
    while (left <= right) {
        int left_val = abs(nums[left]);
        int right_val = abs(nums[right]);

        if (left_val > right_val) {
            res[pos] = left_val * left_val;
            left++;
        } else {
            res[pos] = right_val * right_val;
            right--;
        }
        pos--;
    }
    *returnSize = numsSize;
    return res;
}
