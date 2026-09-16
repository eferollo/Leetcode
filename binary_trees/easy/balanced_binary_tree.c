/**
 * Problem:
 * Given a binary tree, determine if it is height-balanced.
 *
 * Solution:
 * Postorder DFS — compute height bottom-up. At each node check if the
 * height difference between left and right subtrees exceeds 1. Return -1
 * as a sentinel to propagate imbalance upward without a separate pass.
 * The root call returns -1 if any node in the tree is unbalanced.
 *
 * Time Complexity:  O(n)
 * Space Complexity: O(h) -> call stack depth equals tree height h.
 */
#include <stdbool.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int dfs(struct TreeNode *root)
{
    if (root == NULL) {
        return 0;
    }

    int left = dfs(root->left);
    if (left == -1) {
        return -1;
    }

    int right = dfs(root->right);
    if (right == -1) {
        return -1;
    }

    if (abs(left - right) > 1) {
        return -1;
    }
    return 1 + (left > right ? left : right);
}

bool isBalanced(struct TreeNode *root)
{
    return dfs(root) != -1;
}

int main(void)
{
    struct TreeNode *root = NULL;
    bool res = isBalanced(root);
    return EXIT_SUCCESS;
}
