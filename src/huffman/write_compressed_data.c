/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_compressed_data.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 04:09:47 by joltmann          #+#    #+#             */
/*   Updated: 2024/11/02 04:09:47 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "huffman.h"

void	process_symbol_code(FILE *output, char *symbol_code,
		unsigned char *buffer, int *buffer_size)
{
	int	k;
	int	bit;

	k = 0;
	while (symbol_code[k] != '\0')
	{
		bit = symbol_code[k] - '0';
		*buffer = (*buffer << 1) | bit;
		(*buffer_size)++;
		if (*buffer_size == 8)
		{
			fputc(*buffer, output);
			*buffer = 0;
			*buffer_size = 0;
		}
		k++;
	}
}

void	write_compressed_data(FILE *output, char *text, long length,
		char **code_table, int *valid_bits)
{
	unsigned char	buffer;
	int				buffer_size;
	long			i;
	char			*symbol_code;

	buffer = 0;
	buffer_size = 0;
	i = 0;
	while (i < length)
	{
		symbol_code = code_table[(unsigned char)text[i]];
		process_symbol_code(output, symbol_code, &buffer, &buffer_size);
		i++;
	}
	if (buffer_size > 0)
	{
		buffer = buffer << (8 - buffer_size);
		fputc(buffer, output);
		*valid_bits = buffer_size;
	}
	else
		*valid_bits = 8;
}
