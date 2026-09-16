/**
 * Problem:
 * Given the roots of two binary trees root and subRoot, return true if there is
 * a subtree of root with the same structure and node values of subRoot and
 * false otherwise.
 *
 * A subtree of a binary tree tree is a tree that consists of a node in tree and
 * all of this node's descendants. The tree tree could also be considered as a
 * subtree of itself.
 *
 * Solution:
 * DFS on root — at each node check if the subtree rooted there matches
 * subRoot exactly via isSameTree. If not, recurse on the left and right
 * children, short-circuiting as soon as a match is found. Base case: if
 * root is NULL the search is exhausted, return false.
 *
 * Time Complexity:  O(n * m) — for each of the n nodes in root, isSameTree
 *                   runs in O(m) where m is the size of subRoot.
 * Space Complexity: O(h) — call stack depth equals the height of root.
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

bool isSubtree(struct TreeNode *root, struct TreeNode *subRoot)
{
    if (root == NULL || subRoot == NULL) {
        return false;
    }

    if (isSameTree(root, subRoot)) {
        return true;
    }
    bool left = isSubtree(root->left, subRoot);
    if (left) {
        return true;
    }
    bool right = isSubtree(root->right, subRoot);
    if (right) {
        return true;
    }
    return false;
}

int main(void)
{
    struct TreeNode *root = NULL, *sub_root = NULL;
    bool res = isSubtree(root, sub_root);
    return EXIT_SUCCESS;
}
