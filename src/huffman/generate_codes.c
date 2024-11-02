/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_codes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 04:09:27 by joltmann          #+#    #+#             */
/*   Updated: 2024/11/02 04:09:27 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "huffman.h"

void	generate_codes(HuffmanNode *node, char *code, int depth,
		char **code_table)
{
	if (node->left == NULL && node->right == NULL)
	{
		code[depth] = '\0';
		code_table[(unsigned char)node->character] = strdup(code);
		return ;
	}
	code[depth] = '0';
	generate_codes(node->left, code, depth + 1, code_table);
	code[depth] = '1';
	generate_codes(node->right, code, depth + 1, code_table);
}
