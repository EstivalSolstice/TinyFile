#include "huffman.h"

void process_bit(int bit, TreeNode **current, TreeNode *root, FILE *output)
{
    if (bit == 0)
        *current = (*current)->left;
    else
        *current = (*current)->right;
    if ((*current)->left == NULL && (*current)->right == NULL)
    {
        HuffmanData *data = (HuffmanData *)(*current)->data;
        fputc(data->character, output);
        *current = root;
    }
}

void decompress_data(FILE *input, FILE *output, TreeNode *root, long compressed_size, int valid_bits)
{
    TreeNode *current = root;
    int byte;
    long bytes_read = 0;
    int bits_to_process;

    while (bytes_read < compressed_size && (byte = fgetc(input)) != EOF)
	{
        bytes_read++;
        bits_to_process = (bytes_read == compressed_size) ? valid_bits : 8;
        for (int i = 7; i >= 8 - bits_to_process; i--) {
            int bit = (byte >> i) & 1;
            if (bit == 0)
                current = current->left;
            else
                current = current->right;
            if (current->left == NULL && current->right == NULL)
			{
                HuffmanData *data = (HuffmanData *)current->data;
                fputc(data->character, output);
                current = root;
            }
        }
    }
}
