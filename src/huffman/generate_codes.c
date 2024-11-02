#include "huffman.h"

void generate_codes(TreeNode *node, char *code, int depth, char **code_table) {
    if (node->left == NULL && node->right == NULL) {
        code[depth] = '\0';
        HuffmanData *data = (HuffmanData *)node->data;
        code_table[(unsigned char)data->character] = strdup(code);
        return;
    }
    code[depth] = '0';
    generate_codes(node->left, code, depth + 1, code_table);
    code[depth] = '1';
    generate_codes(node->right, code, depth + 1, code_table);
}

