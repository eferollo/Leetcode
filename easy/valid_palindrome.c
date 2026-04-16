/**
 * Problem:
 * A phrase is a palindrome if, after converting all uppercase letters into 
 * lowercase letters and removing all non-alphanumeric characters, it reads 
 * the same forward and backward. Alphanumeric characters include letters and 
 * numbers.
 *
 * Given a string s, return true if it is a palindrome, or false otherwise.
 *
 * Solution:
 * In this solution, we first remove all non-alphanumeric characters and 
 * convert the remaining ones to lowercase. Then, we use two pointers: 
 * one starting from the beginning of the string and the other from the end.
 * We move both pointers toward the center, comparing the characters at each
 * step. If a mismatch is found, we return early; otherwise, if all pairs 
 * match, the string is a palindrome.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool isPalindrome(char* s) {
    int read_pos = 0, write_pos = 0;
    while (s[read_pos] != '\0') {
        if (isalnum(s[read_pos])) {
            s[write_pos++] = tolower(s[read_pos]);
        }
        read_pos++;
    }
    s[write_pos] = '\0';

    int len = strlen(s);
    if (len == 0) {
        return true;
    }
    char *l = s;
    char *r = s + len - 1;

    while (l < r) {
        if (*l != *r) {
            return false;
        }
        l++;
        r--;
    }

    return true;
}

int main(void)
{
    char s[] = "A man, a plan, a canal: Panama";
    bool res = isPalindrome(s);
    return EXIT_SUCCESS;
}
