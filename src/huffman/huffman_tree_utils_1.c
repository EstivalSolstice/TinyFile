/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   huffman_tree_utils_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 04:09:42 by joltmann          #+#    #+#             */
/*   Updated: 2024/11/02 04:30:35 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "huffman.h"

HuffmanNode	*create_node(char character, int frequency)
{
	HuffmanNode	*node;

	node = (HuffmanNode *)malloc(sizeof(HuffmanNode));
	if (node == NULL)
	{
		perror("Failed to allocate memory for HuffmanNode");
		exit(EXIT_FAILURE);
	}
	node->character = character;
	node->frequency = frequency;
	node->left = NULL;
	node->right = NULL;
	return (node);
}


PriorityQueue	*create_priority_queue(int capacity)
{
	PriorityQueue	*queue;

	queue = (PriorityQueue *)malloc(sizeof(PriorityQueue));
	queue->nodes = (HuffmanNode **)malloc(capacity * sizeof(HuffmanNode *));
	queue->size = 0;
	queue->capacity = capacity;
	return (queue);
}

void	swap_nodes(HuffmanNode **a, HuffmanNode **b)
{
	HuffmanNode	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	heapify(PriorityQueue *queue, int index)
{
	int	smallest;
	int	left;
	int	right;

	smallest = index;
	left = 2 * index + 1;
	right = 2 * index + 2;
	if (left < queue->size
		&& queue->nodes[left]->frequency < queue->nodes[smallest]->frequency)
		smallest = left;
	if (right < queue->size
		&& queue->nodes[right]->frequency < queue->nodes[smallest]->frequency)
		smallest = right;
	if (smallest != index)
	{
		swap_nodes(&queue->nodes[smallest], &queue->nodes[index]);
		heapify(queue, smallest);
	}
}

void	insert_node(PriorityQueue *queue, HuffmanNode *node)
{
	int	i;

	i = queue->size++;
	queue->nodes[i] = node;
	while (i && queue->nodes[i]->frequency < queue->nodes[(i - 1)
			/ 2]->frequency)
	{
		swap_nodes(&queue->nodes[i], &queue->nodes[(i - 1) / 2]);
		i = (i - 1) / 2;
	}
}
