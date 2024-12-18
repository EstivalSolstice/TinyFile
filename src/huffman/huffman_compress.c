#include "huffman.h"

static int	open_input_file(const char *input_file, char **text, long *length)
{
	FILE	*input;

	input = fopen(input_file, "r");
	if (input == NULL)
	{
		perror("Failed to open input file");
		return (0);
	}
	fseek(input, 0, SEEK_END);
	*length = ftell(input);
	fseek(input, 0, SEEK_SET);
	*text = (char *)malloc(*length + 1);
	if (*text == NULL)
	{
		perror("Failed to allocate memory for text");
		return (fclose(input), 0);
	}
	if (fread(*text, 1, *length, input) != (size_t) * length)
	{
		perror("Failed to read input file");
		return (free(*text), fclose(input), 0);
	}
	(*text)[*length] = '\0';
	return (fclose(input), 1);
}

static int build_huffman_codes(char *text, char **code_table, TreeNode **root)
{
    int frequency_table[256];
    char code_buffer[256];

    memset(frequency_table, 0, sizeof(frequency_table));
    count_frequencies(text, frequency_table);
    *root = build_huffman_tree(frequency_table);
    if (*root == NULL)
    {
        fprintf(stderr, "Failed to build Huffman tree.\n");
        return (0);
    }
    generate_codes(*root, code_buffer, 0, code_table);
    return (1);
}
static int	open_output_file(const char *output_file, FILE **output)
{
	*output = fopen(output_file, "wb");
	if (*output == NULL)
	{
		perror("Failed to open output file");
		return (0);
	}
	return (1);
}

void huffman_compress(const char *input_file, const char *output_file)
{
    char *text;
    long length;
    char *code_table[256] = {0};
    TreeNode *root;
    FILE *output;
    int valid_bits;

    if (!open_input_file(input_file, &text, &length))
        return;
    int frequency_table[256];
    count_frequencies(text, frequency_table);
    root = build_huffman_tree(frequency_table);
    if (root == NULL)
	{
        free(text);
        return;
    }
    char code_buffer[256];
    generate_codes(root, code_buffer, 0, code_table);
    output = fopen(output_file, "wb");
    if (output == NULL)
	{
        perror("Failed to open output file");
        cleanup_compression(text, root, code_table);
        return;
    }
    write_huffman_tree(output, root);
    write_compressed_data(output, text, length, code_table, &valid_bits);
    fputc(valid_bits, output);
    fclose(output);
    cleanup_compression(text, root, code_table);
}
