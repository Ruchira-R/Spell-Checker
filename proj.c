#include <stdio.h>
#include <stdlib.h>
#include "trie.h"
#include <string.h>

int main()
{
    node *root = create();
    dict_create(root);
    user_input(root);
    free_trie(root);
    free(root);
    printf("\n");
    return 0;
}