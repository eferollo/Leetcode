/**
 * Problem:
 * Given a binary tree root, a node X in the tree is named good if in the path
 * from root to X there are no nodes with a value greater than X.
 *
 * Return the number of good nodes in the binary tree.
 *
 * Solution:
 * DFS while threading down the maximum value seen so far along the
 * root-to-current path (max, not including the current node). At each node,
 * compare root->val against that ancestor max — if root->val >= max the node
 * is good. Then update max with the current node's value before recursing
 * into children, since the current node becomes an ancestor for them.
 * The initial call seeds max with root->val itself, so the root is always
 * counted as good.
 *
 * Time Complexity:  O(n) — every node is visited once.
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

int dfs(struct TreeNode *root, int max)
{
    if (root == NULL) {
        return 0;
    }

    int count = 0;
    if (root->val >= max) {
        count = 1;
    }

    int new_max = root->val > max ? root->val : max;

    int left = dfs(root->left, new_max);
    int right = dfs(root->right, new_max);

    return count + left + right;
}

int goodNodes(struct TreeNode *root)
{
    return dfs(root, root != NULL ? root->val : INT_MIN);
}

int main(void)
{
    struct TreeNode *root = NULL;
    int res = goodNodes(root);
    return EXIT_SUCCESS;
}
