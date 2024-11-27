/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* runningSum(int* nums, int numsSize, int* returnSize) {
    int i, *res;

    res = calloc(numsSize, sizeof(int));
    res[0] = nums[0];
    for(i = 1; i < numsSize; i++) {
        res[i] = nums[i] + res[i-1];
    }
    *returnSize = numsSize;
    return res;
}
