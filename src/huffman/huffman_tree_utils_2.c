/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   huffman_tree_utils_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 04:14:26 by joltmann          #+#    #+#             */
/*   Updated: 2024/11/02 04:17:08 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "huffman.h"

HuffmanNode	*remove_min(PriorityQueue *queue)
{
	HuffmanNode	*min_node;

	min_node = queue->nodes[0];
	queue->nodes[0] = queue->nodes[--queue->size];
	heapify(queue, 0);
	return (min_node);
}

HuffmanNode	*build_huffman_tree(int *frequency_table)
{
	PriorityQueue	*queue;
	int				i;
	HuffmanNode		*left;
	HuffmanNode		*right;
	HuffmanNode		*parent;

	queue = create_priority_queue(256);
	i = 0;
	while (i < 256)
	{
		if (frequency_table[i] > 0)
			insert_node(queue, create_node(i, frequency_table[i]));
		i++;
	}
	while (queue->size > 1)
	{
		left = remove_min(queue);
		right = remove_min(queue);
		parent = create_node('\0', left->frequency + right->frequency);
		parent->left = left;
		parent->right = right;
		insert_node(queue, parent);
	}
	return (remove_min(queue));
}

void	free_huffman_tree(HuffmanNode *root)
{
	if (root == NULL)
		return ;
	free_huffman_tree(root->left);
	free_huffman_tree(root->right);
	free(root);
}

HuffmanNode	*read_huffman_tree(FILE *file)
{
	int			bit;
	int			character;
	HuffmanNode	*node;

	bit = fgetc(file);
	if (bit == EOF)
		return (NULL);
	if (bit == '1')
	{
		character = fgetc(file);
		if (character == EOF)
			return (NULL);
		return (create_node((char)character, 0));
	}
	else if (bit == '0')
	{
		node = create_node('\0', 0);
		node->left = read_huffman_tree(file);
		node->right = read_huffman_tree(file);
		return (node);
	}
	return (NULL);
}
