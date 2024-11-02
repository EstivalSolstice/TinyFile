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


HuffmanNode* create_node(char character, int frequency);
PriorityQueue* create_priority_queue(int capacity);
void swap_nodes(HuffmanNode **a, HuffmanNode **b);
void heapify(PriorityQueue *queue, int index);
void insert_node(PriorityQueue *queue, HuffmanNode *node);
HuffmanNode* remove_min(PriorityQueue *queue);
HuffmanNode* build_huffman_tree(int *frequency_table);
void free_huffman_tree(HuffmanNode *root);
void count_frequencies(const char *text, int *frequency_table);
void generate_codes(HuffmanNode *node, char *code, int depth, char **code_table);
void write_huffman_tree(FILE *file, HuffmanNode *node);
HuffmanNode* read_huffman_tree(FILE *file);
void huffman_compress(const char *input_file, const char *output_file);
void huffman_decompress(const char *input_file, const char *output_file);
void print_tree(HuffmanNode *node, int depth);

void test_compression_decompression_large();

#endif