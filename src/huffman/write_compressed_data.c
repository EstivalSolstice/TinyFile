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

void write_compressed_data(FILE *output, const char *text, long length, char **code_table, int *valid_bits)
{
    unsigned char buffer = 0;
    int buffer_size = 0;

    for (long i = 0; i < length; i++)
	{
        const char *symbol_code = code_table[(unsigned char)text[i]];
        for (int k = 0; symbol_code[k] != '\0'; k++)
		{
            int bit = symbol_code[k] - '0';
            buffer = (buffer << 1) | bit;
            buffer_size++;
            if (buffer_size == 8)
			{
                fputc(buffer, output);
                buffer = 0;
                buffer_size = 0;
            }
        }
    }
    if (buffer_size > 0)
	{
        buffer <<= (8 - buffer_size);
        fputc(buffer, output);
        *valid_bits = buffer_size;
    }
	else
	{
        *valid_bits = 8;
    }
}

