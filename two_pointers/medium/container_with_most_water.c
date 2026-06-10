/**
 * Problem:
 * You are given an integer array height of length n. There are n vertical
 * lines drawn such that the two endpoints of the ith line are (i, 0) and
 * (i, height[i]). Find two lines that together with the x-axis form a
 * container, such that the container contains the most water.
 *
 * Return the maximum amount of water a container can store.
 * Notice that you may not slant the container.
 *
 * Solution:
 * We use a two-pointer approach, starting at the leftmost (i) and
 * rightmost (j) positions. At each step, we compute the area formed
 * by the two lines as:
 *      area = min(height[i], height[j]) * (j - i)
 *
 * We keep track of the maximum area seen so far and update it if the
 * current area is larger.
 *
 * To potentially find a better solution, we move the pointer pointing
 * to the shorter line inward, since the shorter height is the limiting
 * factor. Moving the taller line would only reduce the width without
 * increasing the height.
 *
 * This process continues until the two pointers meet.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
int maxArea(int *height, int heightSize)
{
    int i = 0, j = heightSize - 1;
    int area, dist, max_area = 0;

    while (i < j) {
        dist = j - i;
        area = height[i] <= height[j] ? dist * height[i] : dist * height[j];

        if (area > max_area) {
            max_area = area;
        }

        if (height[i] > height[j]) {
            j--;
        } else {
            i++;
        }
    }
    return max_area;
}

int main(void)
{
    int height[] = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    int res = maxArea(height, 9); // 49
    return 0;
}
