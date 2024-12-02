/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode *newNode(int val) {
    struct TreeNode *x = calloc(1, sizeof(struct TreeNode));
    x->val = val;
    x->left = NULL;
    x->right = NULL;
    return x;
}

int search(int *arr, int val, int start, int end) {
    int i;
    for (i = start; i <= end; i++) {
        if (arr[i] == val) {
            return i;
        }
    }
    return -1;
}

struct TreeNode *build(int *preorder, int *inorder, int *pre_idx, int start, int end) {
    if (start > end) return NULL;

    struct TreeNode *node = newNode(preorder[(*pre_idx)++]);

    if (start == end) return node;

    int in_idx = search(inorder, node->val, start, end);
    node->left = build(preorder, inorder, pre_idx, start, in_idx - 1);
    node->right = build(preorder, inorder, pre_idx, in_idx + 1, end);
    return node;
}

struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize) {
    int pre_idx = 0;
    return build(preorder, inorder, &pre_idx, 0, inorderSize - 1);
}
