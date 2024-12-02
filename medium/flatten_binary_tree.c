/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
void flatten(struct TreeNode* root) {
    if (root == NULL) return;

    flatten(root->left);
    flatten(root->right);

    struct TreeNode *left = root->left;
    struct TreeNode *right = root->right; 

    root->left = NULL;
    root->right = left;

    struct TreeNode *current = root;
    while (current->right != NULL) {
        current = current->right;
    }

    current->right = right;
}
