/**
 * Problem:
 * Given a binary search tree (BST), find the lowest common ancestor (LCA) node
 * of two given nodes in the BST.
 *
 * According to the definition of LCA on Wikipedia: “The lowest common ancestor
 * is defined between two nodes p and q as the lowest node in T that has both p
 * and q as descendants (where we allow a node to be a descendant of itself).”
 *
 * Solution:
 * Postorder DFS — recurse on both subtrees before processing the current node.
 * Base cases: return NULL if root is NULL, return p or q if the current node
 * matches either. After recursing, four outcomes are possible:
 *   - both sides non-NULL: p and q were found in opposite subtrees, so the
 *     current node is the LCA — return root.
 *   - only left non-NULL: both nodes are in the left subtree, propagate left.
 *   - only right non-NULL: both nodes are in the right subtree, propagate
 *     right.
 *   - both NULL: neither p nor q found in this subtree, return NULL.
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

struct TreeNode *lowestCommonAncestor(struct TreeNode *root,
                                      struct TreeNode *p,
                                      struct TreeNode *q)
{
    if (root == NULL) {
        return NULL;
    }

    if (root == p) {
        return p;
    } else if (root == q) {
        return q;
    }

    struct TreeNode *left = lowestCommonAncestor(root->left, p, q);
    struct TreeNode *right = lowestCommonAncestor(root->right, p, q);

    if ((left == p && right == q) || (left == q && right == p)) {
        return root;
    }

    if (left == NULL && right != NULL) {
        return right;
    } else if (left != NULL && right == NULL) {
        return left;
    }

    return NULL;
}

int main(void)
{
    struct TreeNode *root = NULL, *p = NULL, *q = NULL;
    struct TreeNode *res = lowestCommonAncestor(root, p, q);
    return EXIT_SUCCESS;
}
