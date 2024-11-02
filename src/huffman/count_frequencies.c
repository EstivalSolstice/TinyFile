#include "huffman.h"

void count_frequencies(const char *text, int *frequency_table)
{
    memset(frequency_table, 0, 256 * sizeof(int));
    for (int i = 0; text[i] != '\0'; i++)
	{
        frequency_table[(unsigned char)text[i]]++;
    }
}

