#include "file_io.h"

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

int read_file(const char *filename, void **buffer, long *length) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return 0;
    }
    fseek(file, 0, SEEK_END);
    *length = ftell(file);
    fseek(file, 0, SEEK_SET);

    *buffer = malloc(*length);
    if (!*buffer) {
        perror("Failed to allocate memory");
        fclose(file);
        return 0;
    }
    if (fread(*buffer, 1, *length, file) != *length) {
        perror("Failed to read file");
        free(*buffer);
        fclose(file);
        return 0;
    }
    fclose(file);
    return 1;
}

int write_file(const char *filename, void *buffer, long length) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Failed to open file");
        return 0;
    }
    if (fwrite(buffer, 1, length, file) != length) {
        perror("Failed to write file");
        fclose(file);
        return 0;
    }
    fclose(file);
    return 1;
}
