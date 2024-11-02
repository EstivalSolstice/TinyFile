/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   huffman_decompress.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 04:09:37 by joltmann          #+#    #+#             */
/*   Updated: 2024/11/02 04:17:02 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "huffman.h"

static int	open_input_file(const char *input_file, FILE **input,
		long *file_size, int *valid_bits)
{
	*input = fopen(input_file, "rb");
	if (*input == NULL)
	{
		perror("Failed to open input file");
		return (0);
	}
	fseek(*input, 0, SEEK_END);
	*file_size = ftell(*input);
	fseek(*input, -1, SEEK_END);
	*valid_bits = fgetc(*input);
	if (*valid_bits == 0)
		*valid_bits = 8;
	fseek(*input, 0, SEEK_SET);
	return (1);
}

static HuffmanNode	*load_huffman_tree(FILE *input)
{
	HuffmanNode	*root;

	root = read_huffman_tree(input);
	if (root == NULL)
	{
		fprintf(stderr, "Failed to read Huffman tree from file.\n");
		return (NULL);
	}
	return (root);
}

static int	open_output_file(const char *output_file, FILE **output)
{
	*output = fopen(output_file, "w");
	if (*output == NULL)
	{
		perror("Failed to open output file");
		return (0);
	}
	return (1);
}

static void	cleanup_decompression(FILE *input, FILE *output, HuffmanNode *root)
{
	if (input != NULL)
		fclose(input);
	if (output != NULL)
		fclose(output);
	if (root != NULL)
		free_huffman_tree(root);
}

void	huffman_decompress(const char *input_file, const char *output_file)
{
	FILE		*input;
	FILE		*output;
	HuffmanNode	*root;
	long		file_size;
	int			valid_bits;
	long		compressed_start;
	long		compressed_size;

	if (!open_input_file(input_file, &input, &file_size, &valid_bits))
		return ;
	root = load_huffman_tree(input);
	if (root == NULL)
	{
		fclose(input);
		return ;
	}
	compressed_start = ftell(input);
	if (!open_output_file(output_file, &output))
	{
		cleanup_decompression(input, NULL, root);
		return ;
	}
	compressed_size = file_size - compressed_start - 1;
	decompress_data(input, output, root, compressed_size, valid_bits);
	cleanup_decompression(input, output, root);
}
