int removeElement(int* nums, int numsSize, int val) {
    int i, j = numsSize;

    for(i = 0; i < j; i++) {
        if(nums[i] == val) {
            while(j > i && nums[j - 1] == val) {
                j--; 
            }
            if(j > i) {
                nums[i] = nums[j - 1];
                j--;
            }
        }
    }

    return j; 
}
