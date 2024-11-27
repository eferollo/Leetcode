int removeDuplicates(int* nums, int numsSize) {
    int i, pos = 1;

    for(i = 1; i < numsSize; i++) {
        if(nums[i] != nums[i-1]) {
            nums[pos++] = nums[i];
        }
    }
    
    return pos;
}
