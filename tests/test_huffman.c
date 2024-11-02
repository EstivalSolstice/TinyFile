#include "huffman.h"

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
    for (int i = 0; i < 256; i++) {
        if (code_table[i] != NULL) {
            printf("Character '%c': %s\n", i, code_table[i]);
        }
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

    char code[256];
    char *code_table[256] = {0};
    generate_codes(reconstructed_root, code, 0, code_table);

    printf("Reconstructed Huffman Codes:\n");
    for (int i = 0; i < 256; i++) {
        if (code_table[i] != NULL) {
            printf("Character '%c': %s\n", i, code_table[i]);
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

    return 0;
}
