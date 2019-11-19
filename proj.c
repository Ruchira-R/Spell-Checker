#include <stdio.h>
#include <stdlib.h>
#include "trie.h"
#include <string.h>

/*The main function is used to create the root node and pass it onto the dict_create() 
function which creates a trie tree for all the words in the dictionary.txt file.
user_input() function parses through the user.txt file and finds the misspelt word/s calling search() 
and suggest() function is called on the misspelt word/s to suggest up to 4 words which can replace the misspelt word.
The free function frees all the nodes that are present in the trie tree*/
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
