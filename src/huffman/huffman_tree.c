#include "huffman.h"

HuffmanNode* create_node(char character, int frequency)
{
    HuffmanNode *node = (HuffmanNode*)malloc(sizeof(HuffmanNode));
    node->character = character;
    node->frequency = frequency;
    node->left = node->right = NULL;
    return (node);
}

PriorityQueue* create_priority_queue(int capacity)
{
    PriorityQueue *queue = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    queue->nodes = (HuffmanNode**)malloc(capacity * sizeof(HuffmanNode*));
    queue->size = 0;
    queue->capacity = capacity;
    return (queue);
}

void swap_nodes(HuffmanNode **a, HuffmanNode **b)
{
    HuffmanNode *temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(PriorityQueue *queue, int index)
{
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < queue->size && queue->nodes[left]->frequency < queue->nodes[smallest]->frequency)
        smallest = left;
    if (right < queue->size && queue->nodes[right]->frequency < queue->nodes[smallest]->frequency)
        smallest = right;
    if (smallest != index)
	{
        swap_nodes(&queue->nodes[smallest], &queue->nodes[index]);
        heapify(queue, smallest);
    }
}

void insert_node(PriorityQueue *queue, HuffmanNode *node)
{
    int i = queue->size++;
    queue->nodes[i] = node;
    while (i && queue->nodes[i]->frequency < queue->nodes[(i - 1) / 2]->frequency)
	{
        swap_nodes(&queue->nodes[i], &queue->nodes[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

HuffmanNode* remove_min(PriorityQueue *queue)
{
    HuffmanNode *min_node = queue->nodes[0];
    queue->nodes[0] = queue->nodes[--queue->size];
    heapify(queue, 0);
    return (min_node);
}

HuffmanNode* build_huffman_tree(int *frequency_table)
{
    PriorityQueue *queue = create_priority_queue(256);
	int i;

	i = 0;
    while (i < 256)
	{
        if (frequency_table[i] > 0)
            insert_node(queue, create_node(i, frequency_table[i]));
		i++;
    }
    while (queue->size > 1)
	{
        HuffmanNode *left = remove_min(queue);
        HuffmanNode *right = remove_min(queue);
        HuffmanNode *parent = create_node('\0', left->frequency + right->frequency);
        parent->left = left;
        parent->right = right;
        insert_node(queue, parent);
    }
    return (remove_min(queue));
}

void free_huffman_tree(HuffmanNode *root)
{
    if (root == NULL)
		return ;
    free_huffman_tree(root->left);
    free_huffman_tree(root->right);
    free(root);
}
