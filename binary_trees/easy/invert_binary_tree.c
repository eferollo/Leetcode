/**
 * Problem:
 * Given the root of a binary tree, invert the tree, and return its root.
 *
 * Solution:
 * Recursively invert the left and right subtrees, then swap them at the
 * current node. The base case is a NULL node, which is returned as-is.
 * This is a postorder traversal. Children are processed before the swap
 * at the current node.
 *
 * Time Complexity:  O(n) every node is visited once.
 * Space Complexity: O(h) recursive call stack depth equals tree height h,
 *                   O(log n) for a balanced tree, O(n) worst case (skewed).
 */
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode *new_node(int data)
{
    struct TreeNode *x = calloc(1, sizeof(struct TreeNode));
    if (x == NULL) {
        return NULL;
    }
    x->val = data;
    x->left = NULL;
    x->right = NULL;
    return x;
}

struct TreeNode *insert(struct TreeNode *root, int data)
{
    if (root == NULL) {
        return new_node(data);
    }

    if (data <= root->val) {
        root->left = insert(root->left, data);
    } else {
        root->right = insert(root->right, data);
    }
    return root;
}

struct TreeNode *invertTree(struct TreeNode *root)
{
    if (root == NULL) {
        return NULL;
    }
    invertTree(root->left);
    invertTree(root->right);
    struct TreeNode *tmp = root->left;
    root->left = root->right;
    root->right = tmp;
    return root;
}

void free_tree(struct TreeNode *root)
{
    if (root == NULL) {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int main(void)
{
    struct TreeNode *root = NULL;
    root = insert(root, 4);
    root = insert(root, 2);
    root = insert(root, 7);
    root = insert(root, 1);
    root = insert(root, 3);
    root = insert(root, 6);
    root = insert(root, 9);

    struct TreeNode *r = invertTree(root);
    free_tree(r);
    return EXIT_SUCCESS;
}
