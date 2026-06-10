/**
 * Problem:
 * You are given a string s and an integer k. You can choose any character of
 * the string and change it to any other uppercase English character. You can
 * form this operation at most k times.
 *
 * Return the length of the longest substring containing the same letter you
 * can get after performing the above operations.
 *
 * Solution:
 * Sliding window. Expand the window with `right`, track frequency of characters
 * and keep the count of the most frequent one (max_freq). If the number of
 * characters to change (window_size - max_freq) exceeds k, shrink from the
 * left. Keep updating the maximum valid window size.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
#include <stdlib.h>

int characterReplacement(char *s, int k)
{
    int seen[256] = {0};
    int winsize = 0, max_win = 0, max_freq = 0;
    int left = 0, right;

    for (right = 0; s[right] != '\0'; right++) {
        seen[s[right]]++;
        if (seen[s[right]] > max_freq) {
            max_freq = seen[s[right]];
        }

        winsize = right - left + 1;
        while (winsize - max_freq > k) {
            seen[s[left]]--;
            left++;
            winsize = right - left + 1;
        }

        if (winsize > max_win) {
            max_win = winsize;
        }
    }
    return max_win;
}

int main(void)
{
    char str[] = "ABAB";
    int res = characterReplacement(str, 2);
    return EXIT_SUCCESS;
}
