#include "huffman.h"

void count_frequencies(const char *text, int *frequency_table)
{
	int i;
 
    memset(frequency_table, 0, 256 * sizeof(int));
	i = 0;
    while (text[i] != '\0')
	{
        frequency_table[(unsigned char)text[i]]++;
		i++;
    }
}

void generate_codes(HuffmanNode *node, char *code, int depth, char **code_table)
{
    if (node->left == NULL && node->right == NULL)
	{
        code[depth] = '\0';
        code_table[(unsigned char)node->character] = strdup(code);
        return ;
    }
    code[depth] = '0';
    generate_codes(node->left, code, depth + 1, code_table);
    code[depth] = '1';
    generate_codes(node->right, code, depth + 1, code_table);
}

void write_huffman_tree(FILE *file, HuffmanNode *node)
{
    if (!node)
		return ;
    if (!node->left && !node->right)
	{
        fputc('1', file);
        fputc(node->character, file);
    }
	else
	{
        fputc('0', file);
        write_huffman_tree(file, node->left);
        write_huffman_tree(file, node->right);
    }
}

void huffman_compress(const char *input_file, const char *output_file)
{
    FILE *input = fopen(input_file, "r");
    if (!input)
	{
        perror("Failed to open input file");
        return ;
    }
    fseek(input, 0, SEEK_END);
    long length = ftell(input);
    fseek(input, 0, SEEK_SET);
    char *text = (char*)malloc(length + 1);
    fread(text, 1, length, input);
    text[length] = '\0';
    fclose(input);
    int frequency_table[256];
    count_frequencies(text, frequency_table);
    HuffmanNode *root = build_huffman_tree(frequency_table);
    char *code_table[256] = {0};
    char code[256];
    generate_codes(root, code, 0, code_table);
    FILE *output = fopen(output_file, "wb");
    if (!output)
	{
        perror("Failed to open output file");
        free(text);
        free_huffman_tree(root);
        return ;
    }
	write_huffman_tree(output, root);
	long i = 0;
	while (i < length)
	{
        char *code = code_table[(unsigned char)text[i]];
        fputs(code, output);
		i++;
    }
    free(text);
	int j = 0;
    while (i < 256)
	{
        free(code_table[i]);
		i++;
    }
    free_huffman_tree(root);
    fclose(output);
}

HuffmanNode* read_huffman_tree(FILE *file)
{
    int bit = fgetc(file);
    if (bit == EOF)
		return (NULL);
    if (bit == '1')
	{
        char character = fgetc(file);
        return (create_node(character, 0));
    }
	else if (bit == '0')
	{
        HuffmanNode *node = create_node('\0', 0);
        node->left = read_huffman_tree(file);
        node->right = read_huffman_tree(file);
        return (node);
    }
    return (NULL);
}

void huffman_decompress(const char *input_file, const char *output_file)
{
    FILE *input = fopen(input_file, "rb");
    if (!input)
	{
        perror("Failed to open input file");
        return ;
    }
	HuffmanNode *root = read_huffman_tree(input);
	FILE *output = fopen(output_file, "w");
    if (!output)
	{
        perror("Failed to open output file");
        free_huffman_tree(root);
        fclose(input);
        return ;
    }
    HuffmanNode *current = root;
    int bit;
    while ((bit = fgetc(input)) != EOF)
	{
        if (bit == '0')
            current = current->left;
        else if (bit == '1')
            current = current->right;
        if (!current->left && !current->right)
		{
            fputc(current->character, output);
            current = root;
        }
    }
    fclose(input);
    fclose(output);
    free_huffman_tree(root);
}
