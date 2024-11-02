/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_code_table.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 04:09:23 by joltmann          #+#    #+#             */
/*   Updated: 2024/11/02 04:09:23 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "huffman.h"

void	free_code_table(char **code_table)
{
	int	i;

	i = 0;
	while (i < 256)
	{
		if (code_table[i] != NULL)
			free(code_table[i]);
		i++;
	}
}
