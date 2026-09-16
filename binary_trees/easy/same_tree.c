/**
 * Problem:
 * Given the roots of two binary trees p and q, write a function to check if
 * they are the same or not.
 *
 * Two binary trees are considered the same if they are structurally identical,
 * and the nodes have the same value
 *
 * Solution:
 * Recursive preorder DFS on both trees simultaneously. At each step: if
 * exactly one node is NULL the structures differ — return false. If both
 * are NULL the subtrees match — return true. Otherwise check the current
 * values and recurse on left and right subtrees, short-circuiting on the
 * first mismatch.
 *
 * Time Complexity:  O(n) — visits each node at most once.
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

bool isSameTree(struct TreeNode *p, struct TreeNode *q)
{
    if ((p == NULL) != (q == NULL)) {
        return false;
    }

    if (p == NULL && q == NULL) {
        return true;
    }

    bool left = isSameTree(p->left, q->left);
    if (!left) {
        return false;
    }
    bool right = isSameTree(p->right, q->right);
    if (!right) {
        return false;
    }
    return p->val == q->val;
}

int main(void)
{
    struct TreeNode *p = NULL, *q = NULL;
    bool res = isSameTree(p, q);
    return EXIT_SUCCESS;
}
