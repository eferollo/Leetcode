/**
 * Problem:
 * Given n non-negative integers representing an elevation map where the width
 * of each bar is 1, compute how much water it can trap after raining.
 *
 * Solution:
 * We use a two-pointer approach starting from both ends of the array.
 * At each step, we track the maximum height seen so far from the left
 * (max_l) and from the right (max_r).
 *
 * The amount of water trapped at a position depends on the smaller of
 * these two maximums. So:
 * - If max_l <= max_r, we process the left side, since max_l is the limit.
 * - Otherwise, we process the right side, since max_r is the limit.
 *
 * For each position, trapped water = current boundary max - height[i or j].
 * We then move the corresponding pointer inward.
 *
 * Example walkthrough:
 * height = [0,1,0,2,1,0,1,3,2,1,2,1]
 *
 * Step | i | j  | max_l | max_r | action                         | water
 * -------------------------------------------------------------------------
 *  1   | 0 | 11 |   0   |   1   | 0 - height[0]=0  => 0 - 0      | +0
 *  2   | 1 | 11 |   1   |   1   | 1 - height[1]=1  => 1 - 1      | +0
 *  3   | 2 | 11 |   1   |   1   | 1 - height[2]=0  => 1 - 0      | +1
 *  4   | 3 | 11 |   2   |   1   | 1 - height[11]=1 => 1 - 1      | +0
 *  5   | 3 | 10 |   2   |   2   | 2 - height[3]=2  => 2 - 2      | +0
 *  6   | 4 | 10 |   2   |   2   | 2 - height[4]=1  => 2 - 1      | +1
 *  7   | 5 | 10 |   2   |   2   | 2 - height[5]=0  => 2 - 0      | +2
 *  8   | 6 | 10 |   2   |   2   | 2 - height[6]=1  => 2 - 1      | +1
 *  9   | 7 | 10 |   3   |   2   | 2 - height[10]=2 => 2 - 2      | +0
 * 10   | 7 |  9 |   3   |   2   | 2 - height[9]=1  => 2 - 1      | +1
 * 11   | 7 |  8 |   3   |   2   | 2 - height[8]=2  => 2 - 2      | +0
 *
 * Total trapped water = 6
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */

#include <stdlib.h>

int trap(int *height, int heightSize)
{
    int water = 0, i = 0, j = heightSize - 1;
    int max_l = 0, max_r = 0;

    while (i < j) {
        if (height[i] > max_l) {
            max_l = height[i];
        }
        if (height[j] > max_r) {
            max_r = height[j];
        }
        if (max_l <= max_r) {
            water += max_l - height[i];
            i++;
        } else {
            water += max_r - height[j];
            j--;
        }
    }

    return water;
}

int main(void)
{
    int height[] = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    int res = trap(height, 12);
    return EXIT_SUCCESS;
}
