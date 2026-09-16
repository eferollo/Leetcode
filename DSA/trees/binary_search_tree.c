#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left;
    struct node *right;
};

struct node *new_node(int data)
{
    struct node *x = calloc(1, sizeof(struct node));
    if (x == NULL) {
        return NULL;
    }
    x->data = data;
    x->left = NULL;
    x->right = NULL;
    return x;
}

struct node *insert(struct node *root, int data)
{
    if (root == NULL) {
        return new_node(data);
    }

    if (data <= root->data) {
        root->left = insert(root->left, data);
    } else {
        root->right = insert(root->right, data);
    }
    return root;
}

/* depth-first search */
struct node *dfs_search(struct node *root, int data)
{
    if (root == NULL || root->data == data) {
        return root;
    }
    if (data < root->data) {
        return dfs_search(root->left, data);
    }
    return dfs_search(root->right, data);
}

/* breadth-first search */
struct node *bfs_search(struct node *root, int data) {
    if (root == NULL) {
        return root;
    }

    struct node *queue[1024];
    int front = 0, back = 0;

    queue[back++] = root;

    while (front < back) {
        struct node *curr = queue[front++];
        
        if (curr->data == data) {
            return curr;
        }

        if (curr->left != NULL) {
            queue[back++] = curr->left;
        }
        if (curr->right != NULL) {
            queue[back++] = curr->right;
        }
    }
    return NULL;
}

/* find the leftmost node in a subtree (inorder traversal) */
struct node *min_node(struct node *root)
{
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

struct node *delete(struct node *root, int data)
{
    if (root == NULL) {
        return NULL;
    }

    if (data < root->data) {
        root->left = delete(root->left, data);
    } else if (data > root->data) {
        root->right = delete(root->right, data);
    } else {
        if (root->left == NULL) {
            struct node *tmp = root->right;
            free(root);
            return tmp;
        }
        if (root->right == NULL) {
            struct node *tmp = root->left;
            free(root);
            return tmp;
        }
        /* two children: replace with inorder successor */
        struct node *successor = min_node(root->right);
        root->data = successor->data;
        root->right = delete(root->right, successor->data);
    }
    return root;
}

void inorder_traversal(struct node *root)
{
    if (root != NULL) {
        inorder_traversal(root->left);
        printf("%d ", root->data);
        inorder_traversal(root->right);
    }
}

void preorder_traversal(struct node *root)
{
    if (root != NULL) {
        printf("%d ", root->data);
        preorder_traversal(root->left);
        preorder_traversal(root->right);
    }
}

void postorder_traversal(struct node *root)
{
    if (root != NULL) {
        postorder_traversal(root->left);
        postorder_traversal(root->right);
        printf("%d ", root->data);
    }
}

void levelorder_traversal(struct node *root)
{
    if (root == NULL) {
        return;
    }

    struct node *queue[1024];
    int front = 0, back = 0;

    queue[back++] = root;

    while (front < back) {
        struct node *curr = queue[front++];
        printf("%d ", curr->data);
        if (curr->left != NULL) {
            queue[back++] = curr->left;
        }
        if (curr->right != NULL) {
            queue[back++] = curr->right;
        }
    }
}

int tree_height(struct node *root) {
    if (root == NULL) {
        return 0;
    }
    int left = tree_height(root->left);
    int right = tree_height(root->right);
    return 1 + (left > right ? left : right);
}

/* postorder free otherwise we loose the pointers */
void free_tree(struct node *root)
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
    struct node *root = NULL;

    /* build the tree:
     *        10
     *       /  \
     *      5    15
     *     / \     \
     *    3   7    20
     */
    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 15);
    root = insert(root, 3);
    root = insert(root, 7);
    root = insert(root, 20);

    printf("tree height: %d\n", tree_height(root));

    printf("inorder:    ");
    inorder_traversal(root);
    printf("\n");
    printf("preorder:   ");
    preorder_traversal(root);
    printf("\n");
    printf("postorder:  ");
    postorder_traversal(root);
    printf("\n");
    printf("levelorder: ");
    levelorder_traversal(root);
    printf("\n");

    printf("dfs_search 7:  %s\n", dfs_search(root, 7) ? "found" : "not found");
    printf("bfs_search 7:  %s\n", bfs_search(root, 7) ? "found" : "not found");
    printf("dfs_search 99: %s\n", dfs_search(root, 99) ? "found" : "not found");

    root = delete(root, 5);
    printf("after deleting 5 (two children):\n");
    printf("inorder: ");
    inorder_traversal(root);
    printf("\n");

    root = delete(root, 15);
    printf("after deleting 15 (one child):\n");
    printf("inorder: ");
    inorder_traversal(root);
    printf("\n");

    root = delete(root, 10);
    printf("after deleting 10 (root):\n");
    printf("inorder: ");
    inorder_traversal(root);
    printf("\n");

    free_tree(root);
    return EXIT_SUCCESS;
}
