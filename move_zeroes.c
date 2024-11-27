void moveZeroes(int* nums, int numsSize) {
    int i, j, pos;

    pos = 0;
    for(i = 0; i < numsSize; i++) {
        if(nums[i] != 0) {
            nums[pos++] = nums[i]; 
        }
    }

    for(i = pos; i < numsSize; i++) {
        nums[i] = 0;
    }
}
