/**
 * Problem:
 * Given the root of a binary tree, imagine yourself standing on the right side
 * of it, return the values of the nodes you can see ordered from top to bottom.
 *
 * Solution:
 * BFS level by level. At each level, level_size = back - front gives the
 * number of nodes in that level. Process them left to right, enqueueing
 * children for the next level; the last node processed in each level
 * (i == level_size - 1) is the rightmost node visible from that level, so
 * its value is stored at arr[level - 1].
 *
 * Time Complexity:  O(n)
 * Space Complexity: O(n) — queue holds at most one level's worth of nodes
 *                   (O(w), w = max width); output holds one value per level.
 */
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *rightSideView(struct TreeNode *root, int *returnSize)
{
    if (root == NULL) {
        *returnSize = 0;
        return NULL;
    }

    int front = 0, back = 0;
    int level_size, level = 1;
    int *arr = calloc(level, sizeof(int));
    struct TreeNode *queue[2048];

    queue[back++] = root;

    while (front < back) {
        level_size = back - front;
        arr = realloc(arr, level * sizeof(int));

        for (int i = 0; i < level_size; i++) {
            struct TreeNode *curr = queue[front++];
            if (i == level_size - 1) {
                arr[level - 1] = curr->val;
            }
            if (curr->left != NULL) {
                queue[back++] = curr->left;
            }
            if (curr->right != NULL) {
                queue[back++] = curr->right;
            }
        }
        level++;
    }
    *returnSize = level - 1;
    return arr;
}

int main(void)
{
    struct TreeNode *root = NULL;
    int size;
    int *res = rightSideView(root, &size);
    return EXIT_SUCCESS;
}
