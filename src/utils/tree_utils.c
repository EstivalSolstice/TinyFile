#include "utils.h"

TreeNode *create_tree_node(void *data)
{
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    if (node == NULL)
	{
        perror("Failed to allocate memory for TreeNode");
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}
void free_tree(TreeNode *root, void (*free_data)(void *))
{
    if (root == NULL)
        return ;
    free_tree(root->left, free_data);
    free_tree(root->right, free_data);
    if (free_data)
        free_data(root->data);
    free(root);
}
void free_huffman_data(void *data)
{
    free(data);
}