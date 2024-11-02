#include "huffman.h"

void write_huffman_tree(FILE *file, TreeNode *node)
{
    if (node == NULL)
        return ;
    if (node->left == NULL && node->right == NULL)
	{
        fputc('1', file);
        HuffmanData *data = (HuffmanData *)node->data;
        fputc(data->character, file);
    }
	else
	{
        fputc('0', file);
        write_huffman_tree(file, node->left);
        write_huffman_tree(file, node->right);
    }
}
