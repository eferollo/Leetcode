#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * In this problem we need to find the length of the longest substring
 * without duplicates. We have:
 * - A string as input = sequence of characters
 * - An optimization problem = maximum length of substring
 * - A constraint = no duplicates
 *
 * This is a sequence problem with an optimization (maximum length)
 * and a constraint (no duplicates).
 *
 * 1. Identify operations that must be fast:
 *  - Need to check if a character is already in the current substring
 *  - Need to remove characters from the substring efficiently when duplicates
 *    appear
 *
 * 2. Which data structure to use:
 *  - Fast membership check -> hash set (ideal for no duplicates) or hash map
 *  - In C, characters are integers (ASCII 0-255), so an array of size 256 can
 *    act as a easy "hash table" for presence/frequency.
 *
 * 3. Identify strategy to use:
 *   - A sliding window is ideal (left and right pointers)
 *   - The window grows when adding unique characters (moves 1 pos to right)
 *   - The window shrinks from the left when a duplicate breaks the invariant.
 *
 * 4. Define the invariant:
 *   - At any time, the window must contain only unique characters
 *   - Whenever a duplicate is added (frequency > 1), move left until the
 *     variant is restored.
 *
 * 5. Build the algorithm:
 *  - Initialize left = 0, right iterates over the string (left = right)
 *  - For each character at right, mark it as seen.
 *  - If the character count exceeds 1 (duplicate), shrink from left while
 *    updating counts.
 *  - After each step, compute the window length and the maximum length found
 *    until that moment.
 *
 * Space complexity -> O(1)
 * Time complexity -> O(n)    (each char enters and leaves the window)
 *
 */

int lengthOfLongestSubstring(char *s)
{
    int left = 0, maxlen = 0, right, winsize;
    int seen[255] = {0};

    for (right = 0; s[right] != '\0'; right++) {
        seen[s[right]]++;

        while (seen[s[right]] > 1) {
            seen[s[left]]--;
            left++;
        }

        winsize = right - left + 1;
        if (winsize > maxlen) {
            maxlen = winsize;
        }
    }

    return maxlen;
}

int main(void)
{
    char *s = strdup("pwwkew");
    printf("MaxLen: %d\n", lengthOfLongestSubstring(s));
    free(s);
    return 0;
}
