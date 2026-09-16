/**
 * Problem:
 * Given two integer arrays preorder and inorder where preorder is the preorder
 * traversal of a binary tree and inorder is the inorder traversal of the same
 * tree, construct and return the binary tree.
 *
 * Solution:
 * Preorder visits nodes as root -> left -> right, so the very next unvisited
 * element of preorder is always the root of whatever subtree is currently
 * being built. pre_idx tracks this position globally across all recursive
 * calls via a pointer, advancing by exactly one every time a node is created.
 *
 * Inorder visits nodes as left -> root -> right, so once the current root's
 * value is located inside the inorder array (search_idx), every element to
 * its left in that range belongs to the left subtree, and every element to
 * its right belongs to the right subtree. The pair (start, end) tracks the
 * boundaries of the current subtree's range within inorder, shrinking as the
 * recursion descends.
 *
 * At each call: take the next preorder element as the root, find its split
 * point in inorder, recurse on the left range (start, in_idx-1) — which
 * consumes the appropriate number of subsequent preorder elements to build
 * the entire left subtree first, matching preorder's root-left-right order —
 * then recurse on the right range (in_idx+1, end) for the remaining elements.
 *
 * Time Complexity:  O(n^2) worst case — search_idx scans up to n elements
 *                   for each of the n nodes (degenerates on skewed trees).
 *                   Can be improved to O(n) with a hash map from value to
 *                   inorder index.
 * Space Complexity: O(n) — call stack depth up to O(n) worst case (skewed
 *                   tree), plus O(n) for the constructed tree nodes.
 */
#include <stdlib.h>
#include <string.h>

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

int search_idx(int *inorder, int start, int end, int val)
{
    for (int i = start; i <= end; i++) {
        if (inorder[i] == val) {
            return i;
        }
    }
    return -1;
}

struct TreeNode *
build(int *preorder, int *inorder, int *pre_idx, int start, int end)
{
    if (start > end) {
        return NULL;
    }

    struct TreeNode *node = new_node(preorder[(*pre_idx)++]);

    if (start == end) {
        return node;
    }

    int in_idx = search_idx(inorder, start, end, node->val);
    node->left = build(preorder, inorder, pre_idx, start, in_idx - 1);
    node->right = build(preorder, inorder, pre_idx, in_idx + 1, end);
    return node;
}

struct TreeNode *
buildTree(int *preorder, int preorderSize, int *inorder, int inorderSize)
{
    int pre_idx = 0;
    return build(preorder, inorder, &pre_idx, 0, inorderSize - 1);
}

int main(void)
{
    int preorder[5] = {3, 9, 20, 15, 7};
    int inorder[5] = {9, 3, 15, 20, 7};
    struct TreeNode *root = buildTree(preorder, 5, inorder, 5);
    return EXIT_SUCCESS;
}
