//Structure used to create a trie tree.
typedef struct Node
{
    struct Node *all[26];
    int isLeafNode;
} node;

//Function declarations
int search(node *, char *key); // searches for the word, if found,returns 0 else return 1 
node *insert(node *, char *key);// insert the words in the dictionary.txt file onto a trie tree
node *create();//create is used to create a node in the trie tree 
void dict_create(node *);// calls insert on every word found in the dictionary.txt file
int suggest(node *, char *);// gets the prefix string and searches for the prefix
int last_node(node *);//checks if the node has any children or not
void rec_sug(node *, char *);// calls itself recursively by printing out probable replacement words 
void user_input(node *);// Used to parse through the user.txt file
void free_trie(node *);//frees the nodes in the trie.
char *to_lower(char *);//converts all the letters to lowercase
