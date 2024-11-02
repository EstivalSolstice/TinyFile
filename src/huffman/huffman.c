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
    if (!text) {
        perror("Failed to allocate memory for text");
        fclose(input);
        return;
    }
    fread(text, 1, length, input);
    text[length] = '\0';
    fclose(input);

    int frequency_table[256] = {0};
    count_frequencies(text, frequency_table);
    HuffmanNode *root = build_huffman_tree(frequency_table);
    char *code_table[256] = {0};
    char code_buffer[256];
    generate_codes(root, code_buffer, 0, code_table);

    FILE *output = fopen(output_file, "wb");
    if (!output)
    {
        perror("Failed to open output file");
        free(text);
        free_huffman_tree(root);
        for (int i = 0; i < 256; i++) {
            if (code_table[i]) free(code_table[i]);
        }
        return ;
    }

    write_huffman_tree(output, root);

    unsigned char buffer = 0;
    int buffer_size = 0;
	int valid_bits;

    for (long i = 0; i < length; i++)
    {
        char *symbol_code = code_table[(unsigned char)text[i]];
        for (int k = 0; symbol_code[k] != '\0'; k++) {
            buffer = (buffer << 1) | (symbol_code[k] - '0');
            buffer_size++;
            if (buffer_size == 8)
            {
                fputc(buffer, output);
                buffer = 0;
                buffer_size = 0;
            }
        }
    }

	if (buffer_size > 0)
	{
    	buffer = buffer << (8 - buffer_size);
    	fputc(buffer, output);
    	valid_bits = buffer_size;
	}
	else
    	valid_bits = 8;

    fputc(valid_bits, output);

    free(text);
    for (int j = 0; j < 256; j++)
    {
        free(code_table[j]);
    }
    free_huffman_tree(root);
    fclose(output);
}

HuffmanNode* read_huffman_tree(FILE *file)
{
    int bit = fgetc(file);

    if (bit == EOF)
        return NULL;
    if (bit == '1')
	{ 
        int character = fgetc(file);
        if (character == EOF)
            return (NULL);
        return create_node((char)character, 0);
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

    // Get file size
    fseek(input, 0, SEEK_END);
    long file_size = ftell(input);

    // Read valid_bits from last byte
    fseek(input, -1, SEEK_END);
    int valid_bits = fgetc(input);
	if (valid_bits == 0)
    	valid_bits = 8;

    // Reset to beginning of file
    fseek(input, 0, SEEK_SET);

    // Read Huffman tree
    HuffmanNode *root = read_huffman_tree(input);
    if (!root)
    {
        fprintf(stderr, "Failed to read Huffman tree from file.\n");
        fclose(input);
        return;
    }

    // Get position after tree
    long compressed_data_start = ftell(input);

    // Open output file
    FILE *output = fopen(output_file, "w");
    if (!output)
    {
        perror("Failed to open output file");
        free_huffman_tree(root);
        fclose(input);
        return ;
    }

    // Set file pointer to start of compressed data
    fseek(input, compressed_data_start, SEEK_SET);

    // Calculate compressed data size
    long compressed_data_size = file_size - compressed_data_start - 1; // exclude valid_bits byte

    HuffmanNode *current = root;
    int byte;
    long bytes_read = 0;

    while (bytes_read < compressed_data_size && (byte = fgetc(input)) != EOF)
    {
        bytes_read++;
        int bits_to_process = 8;
        if (bytes_read == compressed_data_size)
            bits_to_process = valid_bits;
        for (int i = 7; i >= 8 - bits_to_process; i--)
        {
            int bit = (byte >> i) & 1;
            current = (bit == 0) ? current->left : current->right;

            if (!current->left && !current->right)
            {
                fputc(current->character, output);
                current = root;
            }
        }
    }

    fclose(input);
    fclose(output);
    free_huffman_tree(root);
}
