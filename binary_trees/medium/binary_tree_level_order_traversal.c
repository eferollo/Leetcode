/**
 * Problem:
 * Given the root of a binary tree, return the level order traversal of its
 * nodes' values. (i.e., from left to right, level by level).
 *
 * Solution:
 * Standard BFS using a queue. At the start of each outer loop iteration,
 * level_size = back - front captures exactly how many nodes belong to the
 * current level (since they were all enqueued by the previous level). Process
 * exactly that many nodes: allocate a row of that size, fill it with their
 * values, and enqueue their children for the next level — without those
 * children affecting the count of the current level.
 *
 * Time Complexity:  O(n)
 * Space Complexity: O(n) — output holds every node's value; queue holds at
 *                   most one level's worth of nodes (O(w), w = max width).
 */
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume
 * caller calls free().
 */
int **
levelOrder(struct TreeNode *root, int *returnSize, int **returnColumnSizes)
{
    if (root == NULL) {
        *returnSize = 0;
        return NULL;
    }

    int front = 0, back = 0;
    int level_size, level = 1;
    struct TreeNode *queue[2048];

    *returnColumnSizes = calloc(1, sizeof(int));
    (*returnColumnSizes)[0] = 1;

    int **arr = calloc(1, sizeof(int *));
    arr[0] = calloc((*returnColumnSizes)[0], sizeof(int));

    queue[back++] = root;

    while (front < back) {
        level_size = back - front;
        *returnColumnSizes = realloc(*returnColumnSizes, level * sizeof(int));
        (*returnColumnSizes)[level - 1] = level_size;
        arr = realloc(arr, level * sizeof(int *));
        arr[level - 1] = calloc(level_size, sizeof(int));

        for (int i = 0; i < level_size; i++) {
            struct TreeNode *curr = queue[front++];
            arr[level - 1][i] = curr->val;
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
    int size, *columnsizes;
    int **res = levelOrder(root, &size, &columnsizes);
    return EXIT_SUCCESS;
}
