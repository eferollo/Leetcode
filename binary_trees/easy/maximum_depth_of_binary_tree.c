/**
 * Problem:
 * Given the root of a binary tree, return its maximum depth.
 *
 * A binary tree's maximum depth is the number of nodes along the longest path
 * from the root node down to the farthest leaf node.
 *
 * Solution:
 * Recursively compute the depth of the left and right subtrees, then return
 * 1 + max(left, right) at each node. Base case: a NULL node has depth 0.
 *
 * Time Complexity:  O(n) — every node is visited once.
 * Space Complexity: O(h) — call stack depth equals tree height h,
 *                   O(log n) balanced, O(n) worst case skewed.
 */
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int maxDepth(struct TreeNode *root)
{
    if (root == NULL) {
        return 0;
    }
    int left = maxDepth(root->left);
    int right = maxDepth(root->right);
    return 1 + (left > right ? left : right);
}

int main(void)
{
    struct TreeNode *root = NULL;
    
    int res = maxDepth(root);
    return EXIT_SUCCESS;
}
