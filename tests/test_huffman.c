#include "huffman.h"
#include <sys/stat.h>

void print_tree(HuffmanNode *node, int depth) {
    if (node == NULL) return;
    for (int i = 0; i < depth; i++) printf(" ");
    if (node->left == NULL && node->right == NULL)
        printf("Leaf: '%c'\n", node->character);
    else
        printf("Node\n");
    print_tree(node->left, depth + 1);
    print_tree(node->right, depth + 1);
}



void test_compression_decompression_large() {
    // Create a large input text by repeating "aaaabbc" multiple times
    const char *input_text = "aaaabbc";
    int repeat_count = 1000; // Adjust this number as needed
    size_t input_text_len = strlen(input_text);
    size_t large_input_size = input_text_len * repeat_count;

    // Allocate memory for the large input text
    char *large_input = malloc(large_input_size + 1);
    if (!large_input) {
        perror("Failed to allocate memory for large input");
        return;
    }

    // Build the large input text
    large_input[0] = '\0';
    for (int i = 0; i < repeat_count; i++) {
        strcat(large_input, input_text);
    }

    system("mkdir -p test_output");

    // Write the large input text to a file
    FILE *input = fopen("test_output/input_large.txt", "w");
    if (!input) {
        perror("Failed to open input file for writing");
        free(large_input);
        return;
    }
    fputs(large_input, input);
    fclose(input);

    // Compress the file
    huffman_compress("test_output/input_large.txt", "test_output/compressed_large.bin");

    // Decompress the file
    huffman_decompress("test_output/compressed_large.bin", "test_output/output_large.txt");

    // Read and verify the output
    FILE *output = fopen("test_output/output_large.txt", "r");
    if (!output) {
        perror("Failed to open output file for reading");
        free(large_input);
        return;
    }
    char *decompressed_text = malloc(large_input_size + 1);
    if (!decompressed_text) {
        perror("Failed to allocate memory for decompressed text");
        fclose(output);
        free(large_input);
        return;
    }
    fread(decompressed_text, 1, large_input_size, output);
    decompressed_text[large_input_size] = '\0';
    fclose(output);

    printf("Original Text Length: %zu\n", large_input_size);
    printf("Decompressed Text Length: %zu\n", strlen(decompressed_text));

    if (strcmp(large_input, decompressed_text) == 0) {
        printf("Large Compression and Decompression successful!\n");
    } else {
        printf("Mismatch in large test! There may be an error in the algorithm.\n");
    }

    // Get file sizes
    struct stat input_stat, compressed_stat;
    stat("test_output/input_large.txt", &input_stat);
    stat("test_output/compressed_large.bin", &compressed_stat);

    printf("Input File Size: %lld bytes\n", (long long)input_stat.st_size);
    printf("Compressed File Size: %lld bytes\n", (long long)compressed_stat.st_size);

    // Clean up
    free(large_input);
    free(decompressed_text);
}

void test_frequency_analysis(void)
{
    const char *test_text = "aaaabbc";
    int frequency_table[256] = {0};

	system("mkdir -p test_output");
    
    count_frequencies(test_text, frequency_table);

    for (int i = 0; i < 256; i++) {
        if (frequency_table[i] > 0) {
            printf("Character '%c': %d times\n", i, frequency_table[i]);
        }
    }
}

////////////////////////////////////////////////////////////////////////

void test_tree_building_and_code_generation(void)
{
    const char *test_text = "aaaabbc";
    int frequency_table[256] = {0};
    char *code_table[256] = {0};
    char code[256];

	system("mkdir -p test_output");

    count_frequencies(test_text, frequency_table);
    HuffmanNode *root = build_huffman_tree(frequency_table);

    generate_codes(root, code, 0, code_table);

    printf("Huffman Codes:\n");
	int i = 0;
    while (i < 256)
	{
        if (code_table[i] != NULL)
            printf("Character '%c': %s\n", i, code_table[i]);
		i++;
    }

    free_huffman_tree(root);
}

////////////////////////////////////////////////////////////////////////

void test_write_and_read_tree()
{
    const char *test_text = "aaaabbc";

	system("mkdir -p test_output");

    int frequency_table[256] = {0};
    count_frequencies(test_text, frequency_table);

    HuffmanNode *root = build_huffman_tree(frequency_table);

    FILE *file = fopen("test_output/tree_test.bin", "wb");
    write_huffman_tree(file, root);
    fclose(file);

    file = fopen("test_output/tree_test.bin", "rb");
    HuffmanNode *reconstructed_root = read_huffman_tree(file);
    fclose(file);

	printf("Reconstructed Huffman Tree:\n");
    print_tree(reconstructed_root, 0);

    char code[256];
    char *code_table[256] = {0};
    generate_codes(reconstructed_root, code, 0, code_table);

    printf("Reconstructed Huffman Codes:\n");
	int i = 0;
    for (int i = 0; i < 256; i++) {
        if (code_table[i] != NULL) {
            printf("Character '%c': %s\n", i, code_table[i]);
            free(code_table[i]);
        }
    }

    free_huffman_tree(root);
    free_huffman_tree(reconstructed_root);
}

////////////////////////////////////////////////////////////////////////

void test_compression_decompression() {
    const char *input_text = "aaaabbc";

	system("mkdir -p test_output");
    
    // Write the input text to a file
    FILE *input = fopen("test_output/input.txt", "w");
    fputs(input_text, input);
    fclose(input);

    // Compress the file
    huffman_compress("test_output/input.txt", "test_output/compressed.bin");

    // Decompress the file
    huffman_decompress("test_output/compressed.bin", "test_output/output.txt");

    // Read and verify the output
    FILE *output = fopen("test_output/output.txt", "r");
    char decompressed_text[256];
    fgets(decompressed_text, sizeof(decompressed_text), output);
    fclose(output);

    printf("Original Text: %s\n", input_text);
    printf("Decompressed Text: %s\n", decompressed_text);

    if (strcmp(input_text, decompressed_text) == 0) {
        printf("Compression and Decompression successful!\n");
    } else {
        printf("Mismatch! There may be an error in the algorithm.\n");
    }
}

////////////////////////////////////////////////////////////////////////

int main(void)
{
    printf("Testing Frequency Analysis...\n");
    test_frequency_analysis();

    printf("\nTesting Tree Building and Code Generation...\n");
    test_tree_building_and_code_generation();

    printf("\nTesting Writing and Reading Tree Structure...\n");
    test_write_and_read_tree();

    printf("\nTesting Compression and Decompression...\n");
    test_compression_decompression();

	printf("\nTesting Compression and Decompression with Large File...\n");
    test_compression_decompression_large();

    return 0;
}
