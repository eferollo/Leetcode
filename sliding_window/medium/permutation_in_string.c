/**
 * Problem:
 * Given two strings s1 and s2, return true if s2 contains a permutation of s1
 * or false otherwise.
 *
 * In other words, return true if one of s1's permutations is the substring of
 * s2.
 *
 * Solution:
 * 1st solution:
 * Sliding window with a single frequency array that stores the difference
 * between s1 and the current window in s2. A variable `matches` counts how many
 * characters have matching frequencies (i.e., diff == 0). As the window slides,
 * we update only the incoming and outgoing characters and adjust `matches`.
 * When all 26 characters match, a permutation is found.
 *
 * 2nd solution:
 * Sliding window with two frequency arrays: one for s1 and one for the current
 * window in s2. For each window, we directly compare the arrays using memcmp.
 * The window is updated by adding the new character and removing the old one.
 * Simpler and more readable, but slightly less efficient due to full comparison
 * at each step.
 *
 * Time Complexity:
 * O(n) for both (n = length of s2). The first avoids repeated full comparisons,
 * while the second does O(26) comparison per step (still constant).
 *
 * Space Complexity:
 * O(1) for both — fixed-size arrays of 26 characters.
 */
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/* 1st solution */
bool checkInclusion(char *s1, char *s2)
{
    int freq[26] = {0};
    int i, right, matches = 0;
    int len1 = strlen(s1), len2 = strlen(s2);

    if (len1 > len2) {
        return false;
    }

    for (i = 0; i < len1; i++) {
        freq[s1[i] - 'a']++;
        freq[s2[i] - 'a']--;
    }

    for (i = 0; i < 26; i++) {
        if (freq[i] == 0) {
            matches++;
        }
    }

    for (right = len1; s2[right] != '\0'; right++) {
        if (matches == 26) {
            return true;
        }

        int in = s2[right] - 'a';
        int out = s2[right - len1] - 'a';

        freq[in]--;
        if (freq[in] == 0) {
            matches++;
        } else if (freq[in] == -1) {
            matches--;
        }

        freq[out]++;
        if (freq[out] == 0) {
            matches++;
        } else if (freq[out] == 1) {
            matches--;
        }
    }

    return matches == 26;
}

/* 2nd solution (I prefer) */
bool checkInclusion2(char *s1, char *s2)
{
    int len1 = strlen(s1), len2 = strlen(s2);
    int freq1[26] = {0}, freq2[26] = {0};
    int right;

    if (len1 > len2) {
        return false;
    }

    for (int i = 0; i < len1; i++) {
        freq1[s1[i] - 'a']++;
        freq2[s2[i] - 'a']++;
    }

    for (right = len1;; right++) {
        if (memcmp(freq1, freq2, sizeof(freq1)) == 0) {
            return true;
        }
        if (right == len2) {
            break;
        }

        freq2[s2[right] - 'a']++;
        freq2[s2[right - len1] - 'a']--;
    }

    return false;
}

int main(void)
{
    char s1[] = "ab";
    char s2[] = "aidbaooo";
    bool res = checkInclusion(s1, s2);
    return EXIT_SUCCESS;
}
