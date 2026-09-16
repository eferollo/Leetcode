/**
 * Problem:
 * A path in a binary tree is a sequence of nodes where each pair of adjacent
 * nodes in the sequence has an edge connecting them. A node can only appear in
 * the sequence at most once. Note that the path does not need to pass through
 * the root.
 *
 * The path sum of a path is the sum of the node's values in the path.
 * Given the root of a binary tree, return the maximum path sum of any
 * non-empty path.
 *
 * Solution:
 * Perform a post-order DFS. For every node, compute:
 *
 *   gain(node) = node->val +
 *                max(0, gain(node->left),
 *                         gain(node->right))
 *
 * The value returned to the parent is the maximum sum of a path that:
 *   1. Starts at the current node.
 *   2. Extends downward through at most one child.
 *
 * At each node we also consider the possibility that the maximum path passes
 * through the current node and uses both subtrees:
 *
 *   candidate = left_gain + node->val + right_gain
 *
 * We keep a global maximum and update it with every candidate.
 *
 * Why are negative gains replaced with 0?
 * A path is allowed to start and end at any node, so we are never forced to
 * include a subtree. If a child contributes a negative sum, adding it would
 * only decrease the total path sum:
 *
 *   node->val + (-5) < node->val
 *
 * Therefore, a negative contribution is equivalent to not taking that subtree
 * at all, which contributes 0.
 *
 * Example:
 *
 *         1
 *        / \
 *      -2   3
 *
 * gain(-2) = -2
 * left_gain  = max(-2, 0) = 0
 * right_gain = max(3, 0)  = 3
 *
 * candidate = 0 + 1 + 3 = 4
 *
 * The optimal path is simply 1 -> 3; including -2 would reduce the sum.
 *
 * Time Complexity:  O(n)
 * Space Complexity: O(h) — call stack depth equals tree height h,
 *                   O(log n) balanced, O(n) worst case skewed.
 */
#include <limits.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode *new_node(int val)
{
    struct TreeNode *x = calloc(1, sizeof(struct TreeNode));
    if (x == NULL) {
        return NULL;
    }
    x->val = val;
    x->left = x->right = NULL;
    return x;
}

int dfs(struct TreeNode *root, int *max_path)
{
    if (root == NULL) {
        return 0;
    }

    int left = dfs(root->left, max_path);
    if (left < 0) {
        left = 0;
    }
    int right = dfs(root->right, max_path);
    if (right < 0) {
        right = 0;
    }

    int len = left + root->val + right;
    if (len > *max_path) {
        *max_path = len;
    }
    return root->val + (left > right ? left : right);
}

int maxPathSum(struct TreeNode *root)
{
    if (root == NULL) {
        return 0;
    }
    int max = root->val;
    dfs(root, &max);
    return max;
}

int main(void)
{
    struct TreeNode *root = new_node(1);
    root->left = new_node(-2);
    root->right = new_node(3);
    // root->right = new_node(20);
    // root->right->left = new_node(15);
    // root->right->right = new_node(7);
    int res = maxPathSum(root);
    return EXIT_SUCCESS;
}
