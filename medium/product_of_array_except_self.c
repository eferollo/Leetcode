/**
 * Problem:
 * Given an integer array nums, return an array answer such that answer[i] 
 * is equal to the product of all the elements of nums except nums[i]. 
 * The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit
 * integer. You must write an algorithm that runs in O(n) time and without
 * using the division operation.
 *
 * Example 1:
 *
 * Input: nums = [1,2,3,4]
 * Output: [24,12,8,6]
 *
 * Solution:
 * To solve this problem in linear time we can cleverly use prefix and postfix 
 * product techniques.
 *
 * Prefix product: pre[i] = nums[0] * nums[1] * nums[i-1];
 * Postfix product: post[i] = nums[i+1] * nums [i+2] * nums[len-1];
 *
 * 1. Initialize solution vector to all 1s.
 * 2. Iterate up to numsSize
 * 3. We want to multiply res[i] with prefix product and 
 *    res[len-i-1] with postfix product. 
 *    -> Prefix product iteratively multiplies itself with nums[i].
 *    -> Postfix product iteratively multiplies itself with nums[len-i-1].
 *    After multiplying res[] we update prefix and postfix product.
 *
 * Time Complexity: O(n)
 * Space Complexity O(n)
 */
#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* productExceptSelf(int* nums, int numsSize, int* returnSize) {
    int *res = calloc(numsSize, sizeof(int));
    if (res == NULL) {
        return NULL;
    }

    for (int i = 0; i < numsSize; i++) {
        res[i] = 1;
    }

    int prefix_product = 1;
    int postfix_product = 1;

    for (int i = 0; i < numsSize; i++) {
        res[i] *= prefix_product;
        res[numsSize - i - 1] *= postfix_product;
        prefix_product *= nums[i];
        postfix_product *= nums[numsSize - i - 1];
    }
    *returnSize = numsSize;
    return res;
}

int main(void)
{
    int vec[] = {1, 2, 3 ,4};
    int ret_size = 0;
    int *res = productExceptSelf(vec, 4, &ret_size);
    free(res);
    return EXIT_SUCCESS;
}
