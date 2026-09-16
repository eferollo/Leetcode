/**
 * Problem:
 * Design a data structure that supports adding new words and finding if a
 * string matches any previously added string.
 *
 * Implement the WordDictionary class:
 *  - WordDictionary() Initializes the object.
 *  - void addWord(word) Adds word to the data structure, it can be matched
 *    later.
 *  - bool search(word) Returns true if there is any string in the data
 *    structure that matches word or false otherwise. word may contain dots '.'
 *    where dots can be matched with any letter.
 *
 * Solution:
 * Standard trie (26-ary tree, one branch per lowercase letter) for addWord,
 * identical to a plain Trie's insert: walk/create one node per character,
 * mark endofword at the final node.
 *
 * search handles the wildcard '.' via backtracking DFS. At each character:
 *   - if it's a literal letter, descend into that single child (if it
 *     exists); if missing, fail immediately.
 *   - if it's '.', try every one of the 26 possible children in turn —
 *     recurse into each that exists, and return true as soon as any branch
 *     succeeds. This effectively explores all words consistent with the
 *     wildcard positions.
 * The base case (last character of the remaining word, checked via
 * word[1] == '\0') checks endofword directly rather than recursing one
 * more level with an empty string, avoiding an out-of-bounds index from
 * treating '\0' as a letter ('\0' - 'a' is negative).
 *
 * Time Complexity:  addWord: O(L), L = word length.
 *                   search: O(L) for words without '.', up to O(26^L)
 *                   worst case when every character is '.', since each
 *                   wildcard branches into up to 26 recursive calls.
 *                   Leetcode constraint is 2 dots maximum in a search
 *                   -> O(2^L);
 * Space Complexity: O(N * 26) for the trie structure, N = total nodes
 *                   created across all insertions; O(L) call stack depth
 *                   for search's recursion.
 */
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct wd_node {
    struct wd_node *children[26];
    bool endofword;
} WordDictionary;

WordDictionary *wordDictionaryCreate()
{
    WordDictionary *x = calloc(1, sizeof(*x));
    if (x == NULL) {
        return NULL;
    }
    return x;
}

void wordDictionaryAddWord(WordDictionary *obj, char *word)
{
    if (word == NULL || obj == NULL) {
        return;
    }
    WordDictionary *curr = obj;
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (curr->children[index] == NULL) {
            curr->children[index] = wordDictionaryCreate();
        }
        curr = curr->children[index];
    }
    curr->endofword = true;
}

bool wordDictionarySearch(WordDictionary *obj, char *word)
{
    if (obj == NULL) {
        return false;
    }

    if (*word == '.') {
        for (int i = 0; i < 26; i++) {
            if (obj->children[i] != NULL) {
                if (word[1] == '\0') {
                    if (obj->children[i]->endofword) {
                        return true;
                    }
                } else if (wordDictionarySearch(obj->children[i], word + 1)) {
                    return true;
                }
            }
        }
        return false;
    }

    int index = *word - 'a';
    if (obj->children[index] != NULL) {
        if (word[1] == '\0') {
            return obj->children[index]->endofword;
        }
        return wordDictionarySearch(obj->children[index], word + 1);
    }
    return false;
}

void wordDictionaryFree(WordDictionary *obj)
{
    if (obj == NULL) {
        return;
    }

    for (int i = 0; i < 26; i++) {
        if (obj->children[i] != NULL) {
            wordDictionaryFree(obj->children[i]);
        }
    }
    free(obj);
}

/**
 * Your WordDictionary struct will be instantiated and called as such:
 * WordDictionary* obj = wordDictionaryCreate();
 * wordDictionaryAddWord(obj, word);

 * bool param_2 = wordDictionarySearch(obj, word);

 * wordDictionaryFree(obj);
*/
int main(void)
{
    WordDictionary *obj = wordDictionaryCreate();
    wordDictionaryAddWord(obj, "at");
    wordDictionaryAddWord(obj, "and");
    wordDictionaryAddWord(obj, "an");
    wordDictionaryAddWord(obj, "add");
    wordDictionaryAddWord(obj, "bat");
    bool res = wordDictionarySearch(obj, ".at");
    res = wordDictionarySearch(obj, "a..");
    return EXIT_SUCCESS;
}
