#ifndef DATA_ANALYSIS_H
#define DATA_ANALYSIS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

enum {
    ALGO_HUFFMAN,
    ALGO_ANS,
    ALGO_RLE,
    ALGO_LZ77,
    ALGO_NONE
};

int analyze_data(const char *file_path);

double calculate_entropy(const unsigned char *data, long length);
int check_repetition(const unsigned char *data, long length);
int determine_data_type(const unsigned char *data, long length);

#endif