int pivotIndex(int* nums, int numsSize) {
    int pivot, i, l, r, left = 0, right = 0;

    for(i = 0; i < numsSize; i++) {
        pivot = i;

        for (l = 0; l < pivot; l++) {
            left += nums[l];
        }

        for (r = pivot+1; r < numsSize; r++) {
            right += nums[r];
        }

        if(left == right) {
            return pivot;
        }
        left = 0;
        right = 0;
    }
    return -1;
}

int pivotIndex(int* nums, int numsSize) {
    int left_sum = 0, total_sum = 0, i;

    for(i = 0; i < numsSize; i++) {
        total_sum += nums[i];
    }

    for (i = 0; i < numsSize; i++) {
        if (left_sum == total_sum - left_sum - nums[i]) {
            return i;
        }

        left_sum += nums[i];
    }
    return -1;
}
