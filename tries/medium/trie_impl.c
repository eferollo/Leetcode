/**
 * Problem:
 * A trie (pronounced as "try") or prefix tree is a tree data structure used to
 * efficiently store and retrieve keys in a dataset of strings. There are
 * various applications of this data structure, such as autocomplete and
 * spellchecker.
 *
 * Implement the Trie class:
 * - Trie() Initializes the trie object.
 * - void insert(String word) Inserts the string word into the trie.
 * - boolean search(String word) Returns true if the string word is in the trie
 *   (i.e., was inserted before), and false otherwise.
 * - boolean startsWith(String prefix) Returns true if there is a previously
 *   inserted string word that has the prefix prefix, and false otherwise.
 *
 * Solution:
 * Each Trie node has 26 children pointers (one per lowercase letter) and a
 * boolean flag marking whether a word ends at that node. Inserting a word
 * walks/creates one node per character, descending via children[c - 'a'],
 * and sets endofword = true on the final node. Searching for a word or
 * prefix follows the same descent: if any required child is missing, the
 * string was never inserted (or isn't a prefix of anything inserted) —
 * return false immediately. search additionally requires the final node's
 * endofword flag to be true (the path must end exactly at a complete word,
 * not just pass through it), while startsWith only requires the path to
 * exist, regardless of where words terminate along it. Freeing recurses
 * postorder, freeing all children before the current node.
 *
 * Time Complexity:  O(L) for insert, search, and startsWith, where L is the
 *                   length of the word/prefix -> each character is processed
 *                   once with O(1) array indexing.
 * Space Complexity: O(N * 26) worst case for the trie structure, where N is
 *                   the total number of nodes created across all insertions
 *                   (bounded by total characters inserted); O(L) call stack
 *                   for trieFree's recursion depth.
 */
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct trie {
    struct trie *children[26];
    bool endofword;
} Trie;

Trie *trieCreate()
{
    Trie *x = calloc(1, sizeof(*x));
    if (x == NULL) {
        return NULL;
    }
    return x;
}

void trieInsert(Trie *obj, char *word)
{
    if (word == NULL || obj == NULL) {
        return;
    }
    Trie *curr = obj;
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (curr->children[index] == NULL) {
            curr->children[index] = trieCreate();
        }
        curr = curr->children[index];
    }
    curr->endofword = true;
}

bool trieSearch(Trie *obj, char *word)
{
    if (word == NULL || obj == NULL) {
        return false;
    }
    Trie *curr = obj;
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (curr->children[index] == NULL) {
            return false;
        }
        curr = curr->children[index];
    }
    return (curr != NULL && curr->endofword);
}

bool trieStartsWith(Trie *obj, char *prefix)
{
    if (prefix == NULL || obj == NULL) {
        return false;
    }
    Trie *curr = obj;
    for (int i = 0; i < strlen(prefix); i++) {
        int index = prefix[i] - 'a';
        if (curr->children[index] == NULL) {
            return false;
        }
        curr = curr->children[index];
    }
    return true;
}

void trieFree(Trie *obj)
{
    if (obj == NULL) {
        return;
    }

    for (int i = 0; i < 26; i++) {
        if (obj->children[i] != NULL) {
            trieFree(obj->children[i]);
        }
    }
    free(obj);
}

/**
 * Your Trie struct will be instantiated and called as such:
 * Trie* obj = trieCreate();
 * trieInsert(obj, word);

 * bool param_2 = trieSearch(obj, word);

 * bool param_3 = trieStartsWith(obj, prefix);

 * trieFree(obj);
*/
int main(void)
{
    Trie *obj = trieCreate();
    trieInsert(obj, "apple");
    bool res = trieSearch(obj, "apple");
    res = trieSearch(obj, "app");
    res = trieStartsWith(obj, "app");
    trieInsert(obj, "app");
    res = trieSearch(obj, "app");
    trieFree(obj);
    obj = NULL;
    return EXIT_SUCCESS;
}
