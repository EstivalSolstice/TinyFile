#include "data_analysis.h"

double	calculate_entropy(const unsigned char *data, long length)
{
	int		frequency[256] = {0};
	double	entropy;
	double	prob;

	for (long i = 0; i < length; i++)
	{
		frequency[data[i]]++;
	}
	entropy = 0.0;
	for (int i = 0; i < 256; i++)
	{
		if (frequency[i] > 0)
		{
			prob = (double)frequency[i] / length;
			entropy -= prob * log2(prob);
		}
	}
	return (entropy);
}

int	determine_data_type(const unsigned char *data, long length)
{
	int	printable_count;

	printable_count = 0;
	for (long i = 0; i < length; i++)
	{
		if (data[i] >= 32 && data[i] <= 126)
		{
			printable_count++;
		}
	}
	return ((printable_count > length * 0.8) ? 1 : 0);
}

int	check_repetition(const unsigned char *data, long length)
{
	int	max_repetition;
	int	current_repetition;

	max_repetition = 0;
	current_repetition = 1;
	for (long i = 1; i < length; i++)
	{
		if (data[i] == data[i - 1])
		{
			current_repetition++;
		}
		else
		{
			if (current_repetition > max_repetition)
			{
				max_repetition = current_repetition;
			}
			current_repetition = 1;
		}
	}
	return (max_repetition >= 10 ? 1 : 0);
}

int	analyze_data(const char *file_path)
{
	FILE			*file;
	long			length;
	unsigned char	*data;
	double			entropy;
	int				is_repetitive;
	int				is_text;
	int				algorithm;

	file = fopen(file_path, "rb");
	if (!file)
	{
		perror("Failed to open file for analysis");
		return (ALGO_NONE);
	}
	fseek(file, 0, SEEK_END);
	length = ftell(file);
	fseek(file, 0, SEEK_SET);
	data = (unsigned char *)malloc(length);
	if (!data)
	{
		perror("Failed to allocate memory for data analysis");
		fclose(file);
		return (ALGO_NONE);
	}
	fread(data, 1, length, file);
	fclose(file);
	entropy = calculate_entropy(data, length);
	is_repetitive = check_repetition(data, length);
	is_text = determine_data_type(data, length);
	if (entropy > 7.0)
	{
		algorithm = ALGO_ANS;
	}
	else if (is_repetitive)
	{
		algorithm = ALGO_RLE;
	}
	else if (is_text)
	{
		algorithm = ALGO_HUFFMAN;
	}
	else
	{
		algorithm = ALGO_LZ77;
	}
	free(data);
	return (algorithm);
}
