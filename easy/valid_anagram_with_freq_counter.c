/*
 * This problem asks us to determine if two strings are anagrams 
 * (contain the same characters with the same frequencies). 
 * We can use a frequency counter approach where we increment counts 
 * for characters in the first string and decrement for the second. 
 * If they're anagrams, all counts should balance to zero.
 *
 * Time complexity: O(n)
 * Space complexity: O(1)
 */

bool isAnagram(char* s, char* t) {
    int i;
    int freq[26] = {0};

    if (strlen(t) != strlen(s)) {
        return false;
    }

    for (i = 0; s[i] != '\0'; i++) {
        freq[s[i] - 'a']++;
        freq[t[i] - 'a']--;
    }

    for (i = 0; i < 26; i++) {
        if (freq[i] != 0) {
            return false;
        }
    }
    
    return true;
}
