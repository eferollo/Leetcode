#include <stdatomic.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Problem: Given a string s, return the longest palindromic substring
 *
 * A palindrome is defined by symmetry.
 *
 *   "abba"
 *    ^  ^
 * Characters mirror around a center
 *
 * There are 2 structural forms a palindrome can take:
 *   1. Odd length palindrome:
 *        aba
 *         ^
 *      Center is exactly one character.
 *   2. Even length palindrome
 *        abba
 *         ^^
 *      Center is between two characters.
 *
 * Naive approach: Generate every substring (O(n^2))
 *                 For each substring, check if it's palindrome (O(n))
 *                 Total complexity = O(n^3)
 *
 * Every palindrome in a string must have a center. So instead of checking all
 * substrings, we can try all possible centers.
 *
 * Instead of asking if s[i..j] is palindrome, we can ask how much we can
 * expand starting from a center while maintaining the symmetry?
 *
 * So if we fix a center, we only need to compare:
 *   left char == right char
 * And expand while that holds.
 *
 * For a string of length n:
 *  - Each character can be the center of an odd palindrome
 *    -> n centers
 *  - Each gap between characters can be center of even palindrome
 *    -> n - 1 centers
 *
 * So total centers ~ 2n
 *
 * For each center, we expand outward.
 * Worst case:
 *   Every expansion takes O(n) -> Total: O(n^2)
 *
 * Time Complexity:  O(n^2)
 * Space Complexity: O(1)
 *
 * No extra arrays.
 * No dynamic programming table.
 * Only pointer movement.
 */

void expand_from_center(char *s, int left, int right, int *start, int *maxlen)
{
    int len = strlen(s);
    int current_len;

    while (left >= 0 && right < len && s[left] == s[right]) {
        current_len = right - left + 1;

        if (current_len > *maxlen) {
            *maxlen = current_len;
            *start = left;
        }

        /* expand of 1 position symmetrically */
        left--;
        right++;
    }
}

char *longestPalindrome(char *s)
{
    int len = strlen(s), i;
    int start = 0;
    int maxlen = 1; // at leat one char is always palindrome

    if (len == 0) {
        return strdup("");
    }

    /* Treat every char as the center of a palindrome */
    for (i = 0; i < len; i++) {
        /* Case 1: Odd-length palindrome (single center) */
        expand_from_center(s, i, i, &start, &maxlen);

        /* Case 2: Even-length palindrom (double center) */
        expand_from_center(s, i, i + 1, &start, &maxlen);
    }

    char *sub = calloc(maxlen + 1, sizeof(char));
    strncpy(sub, s + start, maxlen);
    sub[maxlen] = '\0'; // null terminate anyway

    return sub;
}

int main(void)
{
    char *s = strdup("cbbd");
    char *res = longestPalindrome(s);
    printf("Longest palindromic substring: %s\n", res);
    free(s);
    free(res);
    return 0;
}
