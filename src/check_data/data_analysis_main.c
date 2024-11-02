#include "data_analysis.h"
#include <stdio.h>

int	main(int argc, char *argv[])
{
	int	chosen_algorithm;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
		return (1);
	}
	chosen_algorithm = analyze_data(argv[1]);
	switch (chosen_algorithm)
	{
	case ALGO_HUFFMAN:
		printf("Using Huffman Compression\n");
		// Call Huffman compression function
		break ;
	case ALGO_ANS:
		printf("Using ANS Compression\n");
		// Call ANS compression function
		break ;
	case ALGO_RLE:
		printf("Using RLE Compression\n");
		// Call RLE compression function
		break ;
	case ALGO_LZ77:
		printf("Using LZ77 Compression\n");
		// Call LZ77 compression function
		break ;
	default:
		printf("No suitable compression algorithm found.\n");
	}
	return (0);
}
