#include "huffman.h"

TreeNode *create_tree_node(void *data) {
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    if (node == NULL) {
        perror("Failed to allocate memory for TreeNode");
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

PriorityQueue *create_priority_queue(int capacity, int (*compare)(const void *, const void *)) {
    PriorityQueue *queue = (PriorityQueue *)malloc(sizeof(PriorityQueue));
    if (queue == NULL) {
        perror("Failed to allocate memory for PriorityQueue");
        exit(EXIT_FAILURE);
    }
    queue->nodes = (void **)malloc(capacity * sizeof(void *));
    if (queue->nodes == NULL) {
        perror("Failed to allocate memory for PriorityQueue nodes");
        free(queue);
        exit(EXIT_FAILURE);
    }
    queue->size = 0;
    queue->capacity = capacity;
    queue->compare = compare;
    return queue;
}


void swap_nodes(void **a, void **b)
{
    void *temp;

    temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(PriorityQueue *queue, int index)
{
    int smallest;
    int left;
    int right;

    smallest = index;
    left = 2 * index + 1;
    right = 2 * index + 2;

    if (left < queue->size && queue->compare(queue->nodes[left], queue->nodes[smallest]) < 0)
        smallest = left;
    if (right < queue->size && queue->compare(queue->nodes[right], queue->nodes[smallest]) < 0)
        smallest = right;
    if (smallest != index)
    {
        swap_nodes(&queue->nodes[smallest], &queue->nodes[index]);
        heapify(queue, smallest);
    }
}

void insert_node(PriorityQueue *queue, void *node)
{
    int i;

    i = queue->size++;
    queue->nodes[i] = node;
    while (i && queue->compare(queue->nodes[i], queue->nodes[(i - 1) / 2]) < 0)
    {
        swap_nodes(&queue->nodes[i], &queue->nodes[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}


int compare_huffman_nodes(const void *a, const void *b)
{
    const TreeNode *node_a = (const TreeNode *)a;
    const TreeNode *node_b = (const TreeNode *)b;
    const HuffmanData *data_a = (const HuffmanData *)node_a->data;
    const HuffmanData *data_b = (const HuffmanData *)node_b->data;
    return data_a->frequency - data_b->frequency;
}

void free_priority_queue(PriorityQueue *queue)
{
    if (!queue)
		return ;

    free(queue->nodes);
    free(queue);
}
