/**
 * Problem:
 * Given two sorted arrays nums1 and nums2 of size m and n respectively, return
 * the median of the two sorted arrays.
 *
 * The overall run time complexity should be O(log (m+n)).
 *
 * Solution: The key idea is to avoid merging the two arrays
 * (O(n)) and instead find the median in O(log(min(n, m))) using binary search.
 *
 * How to think about it (intuition to remember):
 * Instead of asking "what is the middle element after merging?",
 * we ask:
 *   "Can we split both arrays into a left part and a right part such that:
 *      1) left has half of the elements
 *      2) every element in left <= every element in right ?"
 *
 * If we can find such a partition, the median is immediately known.
 *
 * ------------------------------------------------------------
 * Partition idea:
 *
 * We choose a cut in nums1 (mid1), and that forces a cut in nums2 (mid2)
 * so that total elements on the left are half:
 *
 *   mid1 + mid2 = (n + m + 1) / 2
 *
 * So once we pick mid1, mid2 is determined.
 *
 * Around the cuts we define:
 *
 *   l1 = nums1[mid1 - 1]   r1 = nums1[mid1]
 *   l2 = nums2[mid2 - 1]   r2 = nums2[mid2]
 *
 * (Use INT_MIN / INT_MAX when cut is at boundaries)
 *
 * ------------------------------------------------------------
 * Valid partition condition:
 *
 *   l1 <= r2   AND   l2 <= r1
 *
 * Why this works:
 * - l1 and l2 are the largest elements of the left side
 * - r1 and r2 are the smallest elements of the right side
 * If both conditions hold, then:
 *   max(left) <= min(right)
 * → arrays are correctly split
 *
 * ------------------------------------------------------------
 * Binary search reasoning:
 *
 * We binary search on nums1 (the smaller array) to find the correct cut.
 *
 * - If l1 > r2 -> we took too many elements from nums1
 *   -> move left (high = mid1 - 1)
 *
 * - Else if l2 > r1 -> we took too few from nums1
 *   -> move right (low = mid1 + 1)
 *
 * This works because the condition is monotonic:
 * moving the partition left/right fixes violations.
 *
 * ------------------------------------------------------------
 * Once partition is correct:
 *
 * If total size is even:
 *   median = (max(l1, l2) + min(r1, r2)) / 2
 *
 * If odd:
 *   median = max(l1, l2)
 *
 * Key memory trick:
 *   "Find a cut where left max <= right min"
 *
 * Time Complexity: O(log(min(n, m)))  (binary search on smaller array)
 *
 * Space Complexity: O(1)
 */
#include <limits.h>
#include <stdlib.h>

int max(int a, int b)
{
    return a > b ? a : b;
}

int min(int a, int b)
{
    return a < b ? a : b;
}

double
findMedianSortedArrays(int *nums1, int nums1Size, int *nums2, int nums2Size)
{
    if (nums1Size > nums2Size) {
        return findMedianSortedArrays(nums2, nums2Size, nums1, nums1Size);
    }
    int low = 0, high = nums1Size;
    int mid1, mid2;

    while (low <= high) {
        mid1 = (low + high) / 2;
        mid2 = (nums1Size + nums2Size + 1) / 2 - mid1;

        int l1 = (mid1 == 0) ? INT_MIN : nums1[mid1 - 1];
        int r1 = (mid1 == nums1Size) ? INT_MAX : nums1[mid1];

        int l2 = (mid2 == 0) ? INT_MIN : nums2[mid2 - 1];
        int r2 = (mid2 == nums2Size) ? INT_MAX : nums2[mid2];

        if (l1 <= r2 && l2 <= r1) {
            if ((nums1Size + nums2Size) % 2 == 0) {
                return (max(l1, l2) + min(r1, r2)) / 2.0;
            } else {
                return max(l1, l2);
            }
        }

        if (l1 > r2) {
            high = mid1 - 1;
        } else {
            low = mid1 + 1;
        }
    }

    return 0;
}

int main(void)
{
    int arr1[] = {0, 0, 0, 0, 0};
    int arr2[] = {-1, 0, 0, 0, 0, 0, 1};
    double r = findMedianSortedArrays(arr1, 5, arr2, 7);
    return EXIT_SUCCESS;
}
