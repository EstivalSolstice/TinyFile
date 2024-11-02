#ifndef HUFFMAN_H
# define HUFFMAN_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>

/* Data structures */

typedef struct HuffmanNode {
    char character;
    int frequency;
    struct HuffmanNode *left;
    struct HuffmanNode *right;
} HuffmanNode;

typedef struct PriorityQueue {
    HuffmanNode **nodes;
    int size;
    int capacity;
} PriorityQueue;

/* Function prototypes */

HuffmanNode		*create_node(char character, int frequency);
PriorityQueue	*create_priority_queue(int capacity);
void			swap_nodes(HuffmanNode **a, HuffmanNode **b);
void			heapify(PriorityQueue *queue, int index);
void			insert_node(PriorityQueue *queue, HuffmanNode *node);
HuffmanNode		*remove_min(PriorityQueue *queue);
HuffmanNode		*build_huffman_tree(int *frequency_table);
void			free_huffman_tree(HuffmanNode *root);
HuffmanNode		*read_huffman_tree(FILE *file);

/* Huffman encoding functions */
void			count_frequencies(const char *text, int *frequency_table);
void			generate_codes(HuffmanNode *node, char *code, int depth,
					char **code_table);
void			write_huffman_tree(FILE *file, HuffmanNode *node);
void			huffman_compress(const char *input_file,
					const char *output_file);

/* Huffman decoding functions */
void			huffman_decompress(const char *input_file,
					const char *output_file);

/* Additional helper functions */
void			write_compressed_data(FILE *output, char *text, long length,
					char **code_table, int *valid_bits);
void			process_symbol_code(FILE *output, char *symbol_code,
					unsigned char *buffer, int *buffer_size);
void			decompress_data(FILE *input, FILE *output, HuffmanNode *root,
					long compressed_size, int valid_bits);
void			process_bit(int bit, HuffmanNode **current,
					HuffmanNode *root, FILE *output);
void			free_code_table(char **code_table);

#endif