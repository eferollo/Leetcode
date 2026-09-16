/**
 * Problem:
 * Given the root of a binary tree, return the length of the diameter of the
 * tree.
 *
 * The diameter of a binary tree is the length of the longest path between any
 * two nodes in a tree. This path may or may not pass through the root. The
 * length of a path between two nodes is represented by the number of edges
 * between them.
 *
 * Solution:
 * Postorder DFS — compute the height of left and right subtrees before
 * processing the current node. At each node the longest path through it
 * is left_height + right_height (number of edges). Update a running max
 * via a pointer. The function returns height upward to the parent while
 * updating the diameter as a side effect.
 *
 * Time Complexity:  O(n)
 * Space Complexity: O(h) — call stack depth equals tree height h,
 *                   O(log n) balanced, O(n) worst case skewed.
 */
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int height(struct TreeNode *root, int *max)
{
    if (root == NULL) {
        return 0;
    }
    int left = height(root->left, max);
    int right = height(root->right, max);
    if (left + right > *max) {
        *max = left + right;
    }
    return 1 + (left > right ? left : right);
}

int diameterOfBinaryTree(struct TreeNode *root)
{
    int max = 0;
    height(root, &max);
    return max;
}

int main(void)
{
    struct TreeNode *root = NULL;
    int r = diameterOfBinaryTree(root);
    return EXIT_SUCCESS;
}
