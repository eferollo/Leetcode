/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int maxDepth(struct TreeNode* root) {
    if (root == NULL) return 0;

    int ldepth = maxDepth(root->left);
    int rdepth = maxDepth(root->right);

    return (ldepth > rdepth ? ldepth : rdepth) + 1;
}
