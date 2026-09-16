/**
 * Problem:
 * Given the root of a binary tree, determine if it is a valid binary search
 * tree (BST).
 *
 * A valid BST is defined as follows:
 * - The left subtree of a node contains only nodes with keys strictly less
 *   than the node's key.
 * - The right subtree of a node contains only nodes with keys strictly greater
 *   than the node's key.
 * - Both the left and right subtrees must also be binary search trees
 *
 * Solution:
 * Inorder DFS threading the previously visited value through a pointer.
 * Inorder traversal of a valid BST produces values in strictly ascending
 * order, so the problem reduces to checking that each visited value is
 * strictly greater than the one before it. prev is updated after visiting
 * each node and carried into the right subtree, so the check naturally
 * enforces the BST property across the whole tree, not just parent-child
 * pairs. prev is initialized to INT_MIN so the very first (smallest) node
 * always passes.
 *
 * Time Complexity:  O(n)
 * Space Complexity: O(h) — call stack depth equals tree height h,
 *                   O(log n) balanced, O(n) worst case skewed.
 */
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

bool dfs(struct TreeNode *root, long *prev)
{
    if (root == NULL) {
        return true;
    }

    if (!dfs(root->left, prev)) {
        return false;
    }

    if (*prev >= root->val) {
        return false;
    }

    *prev = root->val;

    return dfs(root->right, prev);
}

bool isValidBST(struct TreeNode *root)
{
    long prev = LONG_MIN;
    return dfs(root, &prev);
}

int main(void)
{
    struct TreeNode *root = NULL;
    bool res = isValidBST(root);
    return EXIT_SUCCESS;
}
