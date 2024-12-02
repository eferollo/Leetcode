/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
bool hasPathSum(struct TreeNode* root, int targetSum) {
    if (root == NULL) return false;

    int sub_sum = targetSum - root->val;

    if (sub_sum == 0 && root->left == NULL && root->right == NULL) {
        return true;
    }

    return hasPathSum(root->left, sub_sum) || hasPathSum(root->right, sub_sum);
}
