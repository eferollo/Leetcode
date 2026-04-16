/*
 * Problem:
 * Given two strings s and t, return true if t is an anagram of s, 
 * and false otherwise.
 *
 * Solution: 
 * Treat string as a sequence of ASCII chars that can be compared
 * to sort them in ascending order. If chars are the same the two strings will
 * be ordered in the same way.
 *
 * Time Complexity: O(n log n)
 * Space Complexity: O(1)
 */

int compare(const void *l1, const void *l2) {
    const char *a = (const char *)l1;
    const char *b = (const char *)l2;

    return strcmp(a,b);
}

bool isAnagram(char* s, char* t) {
    int i, s_len = strlen(s), t_len = strlen(t);

    if (t_len != s_len) {
        return false;
    }

    qsort(s, s_len, sizeof(char), compare);
    qsort(t, t_len, sizeof(char), compare);

    for (i = 0; i < s_len; i++) {
        if (s[i] != t[i]) {
            return false;
        }
    }
    return true;
}
