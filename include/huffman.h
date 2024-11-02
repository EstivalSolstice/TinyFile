#ifndef HUFFMAN_H
# define HUFFMAN_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
#include <sys/stat.h>

/* Data structures */

/* Generic Tree Node */
typedef struct TreeNode {
    void *data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

/* Generic Priority Queue */
typedef struct PriorityQueue {
    void **nodes;
    int size;
    int capacity;
    int (*compare)(const void *, const void *);
} PriorityQueue;

/* Huffman Data */
typedef struct {
    char character;
    int frequency;
} HuffmanData;

/* Function prototypes */

/* Tree Node Functions */
TreeNode        *create_tree_node(void *data);
void            free_tree(TreeNode *root, void (*free_data)(void *));

/* Priority Queue Functions */
PriorityQueue   *create_priority_queue(int capacity, int (*compare)(const void *, const void *));
void            insert_node(PriorityQueue *queue, void *node);
void            *remove_min(PriorityQueue *queue);
void            free_priority_queue(PriorityQueue *queue);

/* Huffman-specific Functions */
void            count_frequencies(const char *text, int *frequency_table);
TreeNode        *build_huffman_tree(int *frequency_table);
void            generate_codes(TreeNode *node, char *code, int depth, char **code_table);
void            write_huffman_tree(FILE *file, TreeNode *node);
TreeNode        *read_huffman_tree(FILE *file);
void            huffman_compress(const char *input_file, const char *output_file);
void            huffman_decompress(const char *input_file, const char *output_file);

/* Helper Functions */
void            write_compressed_data(FILE *output, const char *text, long length, char **code_table, int *valid_bits);
void            decompress_data(FILE *input, FILE *output, TreeNode *root, long compressed_size, int valid_bits);
void            free_code_table(char **code_table);
int             compare_huffman_nodes(const void *a, const void *b);
void            free_huffman_data(void *data);
void			cleanup_compression(char *text, TreeNode *root, char **code_table);
void			cleanup_decompression(FILE *input, FILE *output, TreeNode *root);
void			heapify(PriorityQueue *queue, int index);
void			swap_nodes(void **a, void **b);
void free_priority_queue(PriorityQueue *queue);

#endif
