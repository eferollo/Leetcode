int majorityElement(int* nums, int numsSize) {
    int i, sel, cnt = 0;
    for(i = 0; i < numsSize; i++) {
        if(cnt == 0) {
            sel = nums[i];
            cnt = 1;
        } else if(nums[i] == sel) {
            cnt++;
        } else {
            cnt--;
        }
    }
    return sel;
}
