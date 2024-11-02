#include "file_io.h"
#include <stdio.h>

FILE	*open_file(const char *filename, const char *mode)
{
	FILE	*file;

	file = fopen(filename, mode);
	if (!file)
	{
		perror("File opening failed");
	}
	return (file);
}

void	close_file(FILE *file)
{
	if (file)
	{
		fclose(file);
	}
}
