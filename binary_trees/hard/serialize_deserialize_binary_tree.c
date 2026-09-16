/**
 * Problem:
 * Serialization is the process of converting a data structure or object into a
 * sequence of bits so that it can be stored in a file or memory buffer, or
 * transmitted across a network connection link to be reconstructed later in the
 * same or another computer environment.
 *
 * Design an algorithm to serialize and deserialize a binary tree. There is no
 * restriction on how your serialization/deserialization algorithm should work.
 * You just need to ensure that a binary tree can be serialized to a string and
 * this string can be deserialized to the original tree structure.
 *
 * Clarification: The input/output format is the same as how LeetCode serializes
 * a binary tree. You do not necessarily need to follow this format, so please
 * be creative and come up with different approaches yourself.
 *
 * Solution:
 * Level-order (BFS) traversal for both directions.
 *
 * serialize: queue starts with the root. Each dequeued node writes its value
 * (or "N" for NULL) into a dynamically growing buffer, then enqueues both
 * children unconditionally. A non_null counter tracks how many *real* nodes
 * remain in the queue: it's incremented whenever a non-NULL child is
 * enqueued and decremented whenever a real node is dequeued. The loop runs
 * while non_null > 0, so it stops as soon as no real nodes are left to
 * expand — avoiding a final, useless layer of "N,N,...,N" for the leaves'
 * children that would otherwise come from draining the queue normally.
 *
 * deserialize: tokens are consumed in the exact same level-order sequence
 * they were written. The first token builds the root, which is enqueued.
 * For each dequeued node, the next two tokens are its left and right
 * children — "N" leaves the pointer NULL (and nothing is enqueued for it),
 * any other token creates a node, links it, and enqueues it so its own
 * children get read later. This mirrors serialize's traversal order exactly,
 * which is why the queues stay in sync without needing explicit NULL markers
 * stored in the queue itself.
 *
 * Time Complexity:  O(n) for both serialize and deserialize.
 * Space Complexity: O(n) — output string length is proportional to node
 *                   count; queue holds at most O(w) nodes at a time
 *                   (w = max tree width).
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode *new_node(int val)
{
    struct TreeNode *x = calloc(1, sizeof(struct TreeNode));
    if (x == NULL) {
        return NULL;
    }
    x->val = val;
    x->left = x->right = NULL;
    return x;
}

void append_value(char **encoded, size_t *size, size_t *capacity, int *val)
{
    char buf[32] = {0};
    if (val == NULL) {
        snprintf(buf, sizeof(buf), "N,");
    } else {
        snprintf(buf, sizeof(buf), "%d,", *val);
    }

    size_t len = strlen(buf);
    size_t old_size = *size;

    *size += len;
    while (*size >= *capacity) {
        *capacity *= 2;
        *encoded = realloc(*encoded, *capacity * sizeof(char));
    }
    memcpy(*encoded + old_size, buf, len);
    (*encoded)[*size] = '\0';
}

/** Encodes a tree to a single string. */
char *serialize(struct TreeNode *root)
{
    if (root == NULL) {
        return NULL;
    }

    size_t capacity = 4, size = 0;
    char *encoded = calloc(capacity, sizeof(char));
    struct TreeNode *queue[32768];
    int front = 0, back = 0;

    queue[back++] = root;
    int non_null = 1;

    /*
     * non_null straegy is used to avoid final leaf nodes null encoding.
     * If that isn't an issue, remove non_null and use while (front < back)
     */
    while (non_null > 0) {
        struct TreeNode *curr = queue[front++];

        if (curr == NULL) {
            append_value(&encoded, &size, &capacity, NULL);
            continue;
        }

        non_null--;
        append_value(&encoded, &size, &capacity, &curr->val);

        queue[back++] = curr->left;
        if (curr->left) {
            non_null++;
        }
        queue[back++] = curr->right;
        if (curr->right) {
            non_null++;
        }
    }
    encoded[size - 1] = '\0';
    return encoded;
}

/** Decodes your encoded data to tree. */
struct TreeNode *deserialize(char *data)
{
    if (data == NULL) {
        return NULL;
    }

    struct TreeNode *queue[16384];
    int front = 0, back = 0;

    char *token = strtok(data, ",");
    struct TreeNode *root = new_node(atoi(token));
    queue[back++] = root;
    while (front < back) {
        struct TreeNode *curr = queue[front++];

        token = strtok(NULL, ",");
        if (token && strcmp(token, "N") != 0) {
            curr->left = new_node(atoi(token));
            queue[back++] = curr->left;
        }

        token = strtok(NULL, ",");
        if (token && strcmp(token, "N") != 0) {
            curr->right = new_node(atoi(token));
            queue[back++] = curr->right;
        }
    }
    return root;
}

int main(void)
{
    struct TreeNode *root = new_node(1);
    root->left = new_node(2);
    root->right = new_node(3);
    root->right->left = new_node(4);
    root->right->right = new_node(5);
    char *encoded = serialize(root);
    struct TreeNode *root2 = deserialize(encoded);
    return EXIT_SUCCESS;
}
