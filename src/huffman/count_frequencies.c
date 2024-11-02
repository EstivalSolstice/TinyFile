/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_frequencies.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltmann <joltmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 04:09:12 by joltmann          #+#    #+#             */
/*   Updated: 2024/11/02 04:09:12 by joltmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "huffman.h"

void	count_frequencies(const char *text, int *frequency_table)
{
	int	i;

	i = 0;
	memset(frequency_table, 0, 256 * sizeof(int));
	while (text[i] != '\0')
	{
		frequency_table[(unsigned char)text[i]]++;
		i++;
	}
}
