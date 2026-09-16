/**
 * Problem:
 * Given the root of a binary search tree, and an integer k, return the kth
 * smallest value (1-indexed) of all the values of the nodes in the tree.
 *
 * Solution:
 * Inorder traversal visits BST nodes in ascending order, so the k-th visited
 * node is the k-th smallest value. Thread k and result through pointers
 * across recursive calls. Decrement k at each visited node; when it hits
 * zero, record the value and return true to signal "found," which
 * short-circuits the remaining recursion (left subtree first, then current
 * node, then right subtree only if not yet found) without traversing the
 * rest of the tree.
 *
 * Time Complexity:  O(h + k) — descends to the leftmost node (O(h)) then
 *                   visits k nodes in ascending order before stopping.
 * Space Complexity: O(h) — call stack depth equals tree height h,
 *                   O(log n) balanced, O(n) worst case skewed.
 */
#include <stdbool.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

bool inorder(struct TreeNode *root, int *k, int *result)
{
    if (root == NULL) {
        return false;
    }

    if (inorder(root->left, k, result)) {
        return true;
    }

    (*k)--;
    if (*k == 0) {
        *result = root->val;
        return true;
    }
    return inorder(root->right, k, result);
}

int kthSmallest(struct TreeNode *root, int k)
{
    int result = 0;
    inorder(root, &k, &result);
    return result;
}

int main(void)
{
    struct TreeNode *root = NULL;
    int res = kthSmallest(root, 1);
    return EXIT_SUCCESS;
}
