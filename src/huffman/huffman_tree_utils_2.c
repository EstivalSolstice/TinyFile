#include "huffman.h"

void *remove_min(PriorityQueue *queue)
{
    void *min_node;

    min_node = queue->nodes[0];
    queue->nodes[0] = queue->nodes[--queue->size];
    heapify(queue, 0);
    return (min_node);
}

TreeNode *build_huffman_tree(int *frequency_table)
{
    PriorityQueue *queue = create_priority_queue(256, compare_huffman_nodes);
    if (queue == NULL)
        return (NULL);

    for (int i = 0; i < 256; i++)
	{
        if (frequency_table[i] > 0)
		{
            HuffmanData *data = (HuffmanData *)malloc(sizeof(HuffmanData));
            if (data == NULL)
			{
                perror("Failed to allocate memory for HuffmanData");
                free_priority_queue(queue);
                return (NULL);
            }
            data->character = (char)i;
            data->frequency = frequency_table[i];
            TreeNode *node = create_tree_node(data);
            insert_node(queue, node);
        }
    }

    while (queue->size > 1)
	{
        TreeNode *left = remove_min(queue);
        TreeNode *right = remove_min(queue);
        int combined_frequency = ((HuffmanData *)left->data)->frequency + ((HuffmanData *)right->data)->frequency;
        HuffmanData *data = (HuffmanData *)malloc(sizeof(HuffmanData));
        if (data == NULL)
		{
            perror("Failed to allocate memory for HuffmanData");
            free_tree(left, free_huffman_data);
            free_tree(right, free_huffman_data);
            free_priority_queue(queue);
            return NULL;
        }
        data->character = '\0';
        data->frequency = combined_frequency;
        TreeNode *parent = create_tree_node(data);
        parent->left = left;
        parent->right = right;
        insert_node(queue, parent);
    }
    TreeNode *root = remove_min(queue);
    free_priority_queue(queue);
    return (root);
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

TreeNode *read_huffman_tree(FILE *file)
{
    int bit = fgetc(file);
    if (bit == EOF)
        return NULL;

    if (bit == '1')
	{
        int character = fgetc(file);
        if (character == EOF)
            return NULL;
        HuffmanData *data = (HuffmanData *)malloc(sizeof(HuffmanData));
        if (data == NULL)
		{
            perror("Failed to allocate memory for HuffmanData");
            exit(EXIT_FAILURE);
        }
        data->character = (char)character;
        data->frequency = 0;
        return create_tree_node(data);
    }
	else if (bit == '0')
	{
        TreeNode *node = create_tree_node(NULL);
        node->left = read_huffman_tree(file);
        node->right = read_huffman_tree(file);
        return node;
    }
    return (NULL);
}

void cleanup_compression(char *text, TreeNode *root, char **code_table)
{
    free(text);
    free_code_table(code_table);
    free_tree(root, free_huffman_data);
}
void cleanup_decompression(FILE *input, FILE *output, TreeNode *root)
{
    if (input != NULL)
        fclose(input);
    if (output != NULL)
        fclose(output);
    if (root != NULL)
        free_tree(root, free_huffman_data);
}
