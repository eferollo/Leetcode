/**
 * Problem:
 * Given an m x n board of characters and a list of strings words, return all
 * words on the board. Each word must be constructed from letters of
 * sequentially adjacent cells, where adjacent cells are horizontally or
 * vertically neighboring. The same letter cell may not be used more than once
 * in a word.
 *
 * Solution:
 * Build a trie from the words list, then run a backtracking DFS from every
 * cell on the board, navigating the trie simultaneously with the board path.
 *
 * Trie construction: insert all target words so that any valid board path can
 * be checked character by character in O(1) per step — if the current cell's
 * letter has no child in the trie at the current node, the entire subtree is
 * pruned immediately, avoiding exploring paths that can't match any word.
 *
 * DFS from each cell (r, c): descend into trie->children[ch - 'a'] for the
 * current cell's character, append it to a running path buffer, mark the cell
 * visited to prevent reuse within the same word, then recurse in all four
 * directions. On return, unmark the cell (backtrack) so other paths can reuse
 * it. If the current trie node has endofword set, the path accumulated so far
 * is a found word — copy it into the result and clear endofword to prevent
 * duplicates if the same word is reachable via multiple paths.
 *
 * The outer loop starts a fresh DFS from every board cell as the potential
 * first character, ensuring all starting positions are explored.
 *
 * Time Complexity:  O(W * L) to build the trie (W words of average length L),
 *                   plus O(m * n * 4^L) for DFS — each of the m*n cells
 *                   starts a DFS that branches at most 4 ways per step up to
 *                   depth L (longest word). Trie pruning makes the practical
 *                   cost much lower than the theoretical worst case.
 * Space Complexity: O(W * L) for the trie; O(m * n) for the visited matrix;
 *                   O(L) for the path buffer and DFS call stack depth.
 */
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

struct trie_node {
    struct trie_node *children[26];
    bool endofword;
};

struct trie_node *trie_create()
{
    struct trie_node *x = calloc(1, sizeof(*x));
    if (x == NULL) {
        return NULL;
    }
    return x;
}

void trie_insert(struct trie_node *obj, char *word)
{
    if (word == NULL || obj == NULL) {
        return;
    }
    struct trie_node *curr = obj;
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (curr->children[index] == NULL) {
            curr->children[index] = trie_create();
        }
        curr = curr->children[index];
    }
    curr->endofword = true;
}

bool trie_search(struct trie_node *obj, char *word)
{
    if (word == NULL || obj == NULL) {
        return false;
    }
    struct trie_node *curr = obj;
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (curr->children[index] == NULL) {
            return false;
        }
        curr = curr->children[index];
    }
    return (curr != NULL && curr->endofword);
}

void dfs(int r,
         int c,
         struct trie_node *node,
         char **board,
         bool **visited,
         int rows,
         int cols,
         char ***ret,
         int *capacity,
         int *size,
         char *path,
         int depth)
{
    if (r < 0 || c < 0 || r >= rows || c >= cols || visited[r][c]) {
        return;
    }

    char ch = board[r][c];
    int idx = ch - 'a';

    if (node->children[idx] == NULL) {
        return;
    }

    node = node->children[idx];

    path[depth] = ch;
    path[depth + 1] = '\0';

    if (node->endofword) {
        node->endofword = false; // prevent duplicates

        if (*size == *capacity) {
            *capacity *= 2;
            *ret = realloc(*ret, *capacity * sizeof(char *));
        }

        (*ret)[(*size)++] = strdup(path);
    }

    visited[r][c] = true;

    dfs(r - 1, c, node, board, visited, rows, cols, ret, capacity, size, path, depth + 1);
    dfs(r + 1, c, node, board, visited, rows, cols, ret, capacity, size, path, depth + 1);
    dfs(r, c - 1, node, board, visited, rows, cols, ret, capacity, size, path, depth + 1);
    dfs(r, c + 1, node, board, visited, rows, cols, ret, capacity, size, path, depth + 1);

    visited[r][c] = false;
}

void trie_free(struct trie_node *obj)
{
    if (obj == NULL) {
        return;
    }

    for (int i = 0; i < 26; i++) {
        if (obj->children[i] != NULL) {
            trie_free(obj->children[i]);
        }
    }
    free(obj);
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char **findWords(char **board,
                 int boardSize,
                 int *boardColSize,
                 char **words,
                 int wordsSize,
                 int *returnSize)
{
    struct trie_node *trie = trie_create();
    if (trie == NULL) {
        return NULL;
    }

    for (int i = 0; i < wordsSize; i++) {
        trie_insert(trie, words[i]);
    }

    int capacity = 2, size = 0;
    char **ret = calloc(capacity, sizeof(char *));
    bool **visited = calloc(boardSize, sizeof(bool *));
    for (int i = 0; i < boardSize; i++) {
        visited[i] = calloc(boardColSize[i], sizeof(bool));
    }
    char path[16] = {0};

    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardColSize[i]; j++) {
            dfs(i, j, trie, board, visited, boardSize, boardColSize[i], &ret, &capacity, &size, path, 0);
        }
    }

    // free visited matrix
    for (int i = 0; i < boardSize; i++) {
        if (visited[i] != NULL) {
            free(visited[i]);
        }
    }

    free(visited);
    trie_free(trie);
    *returnSize = size;
    return ret;
}

int main(void)
{
    char *board[] = {"oaan", "etae", "ihkr", "iflv"};

    int boardSize = 4;
    int boardColSize[] = {4, 4, 4, 4};

    char *words[] = {"oath", "pea", "eat", "rain"};

    int wordsSize = sizeof(words) / sizeof(words[0]);

    int returnSize = 0;
    char **res = findWords(board,
                           boardSize,
                           boardColSize,
                           words,
                           wordsSize,
                           &returnSize);
    return EXIT_SUCCESS;
}
