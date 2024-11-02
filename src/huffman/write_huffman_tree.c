/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_huffman_tree.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 04:09:51 by joltmann          #+#    #+#             */
/*   Updated: 2024/11/02 04:09:51 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "huffman.h"

void	write_huffman_tree(FILE *file, HuffmanNode *node)
{
	if (node == NULL)
		return ;
	if (node->left == NULL && node->right == NULL)
	{
		fputc('1', file);
		fputc(node->character, file);
	}
	else
	{
		fputc('0', file);
		write_huffman_tree(file, node->left);
		write_huffman_tree(file, node->right);
	}
}
