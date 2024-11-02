#ifndef HUFFMAN_H
# define HUFFMAN_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

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


/*   Huffman_tree   */
HuffmanNode* create_node(char character, int frequency);
PriorityQueue* create_priority_queue(int capacity);
void insert_node(PriorityQueue *queue, HuffmanNode *node);
HuffmanNode* remove_min(PriorityQueue *queue);
HuffmanNode* build_huffman_tree(int *frequency_table);
void free_huffman_tree(HuffmanNode *root);

/*   Huffman   */
void count_frequencies(const char *text, int *frequency_table);
void generate_codes(HuffmanNode *root, char *code, int depth, char **code_table);
void huffman_compress(const char *input_file, const char *output_file);
void huffman_decompress(const char *input_file, const char *output_file);
void write_huffman_tree(FILE *file, HuffmanNode *node);
HuffmanNode* read_huffman_tree(FILE *file);

#endif