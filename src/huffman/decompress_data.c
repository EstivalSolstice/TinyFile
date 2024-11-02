/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decompress_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 04:09:18 by joltmann          #+#    #+#             */
/*   Updated: 2024/11/02 04:33:38 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "huffman.h"

void	process_bit(int bit, HuffmanNode **current, HuffmanNode *root,
		FILE *output)
{
	if (bit == 0)
		*current = (*current)->left;
	else
		*current = (*current)->right;
	if ((*current)->left == NULL && (*current)->right == NULL)
	{
		fputc((*current)->character, output);
		*current = root;
	}
}

void	decompress_data(FILE *input, FILE *output, HuffmanNode *root,
		long compressed_size, int valid_bits)
{
	HuffmanNode	*current;
	int			byte;
	long		bytes_read;
	int			bits_to_process;
	int			bit;
	int			i;

	current = root;
	bytes_read = 0;
	while (bytes_read < compressed_size && (byte = fgetc(input)) != EOF)
	{
		bytes_read++;
		bits_to_process = 8;
		if (bytes_read == compressed_size)
			bits_to_process = valid_bits;
		i = 7;
		while (i >= 8 - bits_to_process)
		{
			bit = (byte >> i) & 1;
			process_bit(bit, &current, root, output);
			i--;
		}
	}
}

// void	process_bit(int bit, HuffmanNode **current, HuffmanNode *root,
// 			FILE *output)
// {
// 	if (bit == 0)
// 		*current = (*current)->left;
// 	else
// 		*current = (*current)->right;
// 	if ((*current)->left == NULL && (*current)->right == NULL)
// 	{
// 		fputc((*current)->character, output);
// 		*current = root;
// 	}
// }

// static void	process_byte(int byte, int bits_to_process, HuffmanNode **current,
// 				HuffmanNode *root, FILE *output)
// {
// 	int	i;
// 	int	bit;

// 	i = 7;
// 	while (i >= 8 - bits_to_process)
// 	{
// 		bit = (byte >> i) & 1;
// 		process_bit(bit, current, root, output);
// 		i--;
// 	}
// }

// void	decompress_data(FILE *input, FILE *output, HuffmanNode *root,
// 			long compressed_size, int valid_bits)
// {
// 	HuffmanNode	*current;
// 	int			byte;
// 	long		bytes_read;
// 	int			bits_to_process;

// 	current = root;
// 	bytes_read = 0;
// 	byte = fgetc(input);
// 	while (bytes_read < compressed_size && byte != EOF)
// 	{
// 		bytes_read++;
// 		bits_to_process = 8;
// 		if (bytes_read == compressed_size)
// 			bits_to_process = valid_bits;
// 		process_byte(byte, bits_to_process, &current, root, output);
// 	}
// }