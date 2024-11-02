#include "main.h"
#include "huffman.h"
#include "rle.h"
#include "file_io.h"

// void	print_usage(void)
// {
// 	printf("Usage: ./tiny_file.exe -c|-d <input_file> <output_file> --algorithm <huffman|rle>\n");
// }

// int	main(int argc, char *argv[])
// {
// 	if (argc != 6)
// 	{
// 		print_usage();
// 		return (1);
// 	}

//     int compress = (strcmp(argv[1], "-c") == 0);
//     char *input_file = argv[2];
//     char *output_file = argv[3];
//     char *algorithm = argv[5];

// 	if (strcmp(algorithm, "huffman") == 0)
// 	{
// 		if (compress)
// 			huffman_compress(input_file, output_file);
// 		else
// 			huffman_decompress(input_file, output_file);
// 	}
// 	else if (strcmp(algorithm, "rle") == 0)
// 	{
// 		if (compress)
// 			rle_compress(input_file, output_file);
// 		else
// 			rle_decompress(input_file, output_file);
// 	}
// 	else
// 	{
// 		print_usage();
// 		return (1);
// 	}

// 	return (0);
// }
