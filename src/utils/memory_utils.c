#include "utils.h"

void free_code_table(char **code_table)
{
    for (int i = 0; i < 256; i++)
	{
        if (code_table[i] != NULL)
            free(code_table[i]);
    }
}

