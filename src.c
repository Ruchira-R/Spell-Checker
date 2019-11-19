
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"

//count is used to limit the number of words that are suggested
int count = 1;

/*Search function is used to search for a given word in the trie tree.
Each and every word in the user.txt file(input file) are passed as key in the search function 
to check whether the given word exists in the tree or not.Return 1 if true, 0 if otherwise.*/
int search(node *root, char *key)
{
    node *t = root;
    char str[100];
    strcpy(str, key);
    if (root == NULL)
        return 0;
    int i, index;
    int l = strlen(key);
    for (i = 0; i < l; i++)
    {
        index = *key - 'a';
        if (t->all[index])
        {
            t = t->all[index];
        }

        else
        {
            return 0;
        }
        *key++;
    }
    if (t->isLeafNode && str[i] == '\0')
    {
        return 1;
    }
    return 0;
}

/*Insert node is to insert all the words in the dictionary.txt file onto the trie tree.
Each and every word in the dictionary.txt file are passed as key and are mapped onto the trie
tree.*/
node *insert(node *root, char *key)
{
    int l = strlen(key);
    int i, index;
    node *temp = root;
    for (i = 0; i < l; i++)
    {
        index = *key - 'a';
        if (!temp->all[index])
        {
            temp->all[index] = create();
        }
        temp = temp->all[index];
        *key++;
    }
    temp->isLeafNode = 1;
    return root;
}

/*Create is used to allocate memory for a new node that is created in the trie tree.*/

node *create()
{
    node *n = (node *)malloc(sizeof(node));
    n->isLeafNode = 0;
    int i;
    for (i = 0; i < 26; i++)
    {
        n->all[i] = NULL;
    }
    return n;
}

/*This function parses through the dictionary.txt file and passes every word in this file 
as key to the insert() function which maps it onto the trie tree*/
void dict_create(node *root)
{
    FILE *fp;
    int i = 0, f;
    char *c;
    char str[40], s[40];
    fp = fopen("dictionary.txt", "r");
    while (fgets(str, 30, fp) != NULL)
    {
        c = strtok(str, "\n");
        root = insert(root, c);
    }

    fclose(fp);
}

/*The last node function is used to check whether or not a given node has any children.
Returns 1 if true,0 otherwise*/
int last_node(node *temp)
{
    int i;
    for (i = 0; i < 26; i++)
    {
        if (temp->all[i])
        {
            return 0;
        }
    }
    return 1;
}

/*The suggest function is used to find probable words to replace the misspelt word.
It does it's job by doing a prefix search on the trie tree created and calls rec_sug() recursively
to find atmost four words to replace the given misspelt word.*/
int suggest(node *root, char *key)
{
    node *temp = root;
    int l, index;
    char str[100];
    strcpy(str, key);
    int n = strlen(key);
    for (l = 0; l < n; l++)
    {
        index = *key - 'a';
        if (temp->all[index])
        {
            temp = temp->all[index];
            *key++;
        }
        else
            return -1;
    }
    int word = (temp->isLeafNode == 1); // prefix as a word
    int last = last_node(temp);         //prefix is a last node of the tree
    if (word && last)     
    {
        return -1;
    }
    if (!last)
    {
        count = 0; // count is initialzied to zero after suggest() is called on a misspelt word
        rec_sug(temp, str);
    }
}

/*A recursive function which is used to find all probable words with a given prefix.
This function is called when the last letter of the given prefix is not a last node, 
suggesting that there are more words with the given prefix*/
void rec_sug(node *root, char *key)
{
    int i, j = 0;
    char c;
    if (root->isLeafNode)
    {
        if (count <= 3)
        {
            printf(" %s ", key);
        }
        count++;
    }
    if (last_node(root))
    {
        return;
    }
    for (i = 0; i < 26; i++)
    {
        if (root->all[i])
        {
            c = 97 + i;
            strncat(key, &c, 1);
            rec_sug(root->all[i], key);
            while (key[j] != '\0')
            {
                j++;
            }
            key[j - 1] = '\0';
        }
    }
}

/*Used to read through the user input file user.txt and find the misspelt words 
and pass it's prefix to the suggest() function which takes care of printing out the probable words.*/
void user_input(node *root)
{
    FILE *fp;
    char *c;
    char sug[20];
    char str[200];
    int i = 0 , j , l , sug_out , error_out=0 ; // sug_out gives the output of suggest and error_out is to print the erroneous words
    
    fp = fopen("user.txt", "r"); 
    while (fgets(str, 200, fp) != NULL)
    {
        c = strtok(str, " ");
        while (c != NULL)
        {
            l = strlen(c);
            if (l >= 4)
            {
                strncpy(sug, c, 4);
                sug[4] = '\0';
            }
            else
            {
                strncpy(sug, c, l);
                sug[l] = '\0';
            }
            i = search(root, c);
            if (!i)
            {
                    printf("\n\n");
                    error_out++;
                    if(error_out==1) printf("ERRONEOUS WORDS : \n\n");
                    printf("%s : ", c);        
                    sug_out = suggest(root, sug);
                    if(sug_out == -1)
                {
                            printf("Sorry no matching strings found!");
                }
                    printf("\n");
            }
            c = strtok(NULL, " ");
        }
    }
}

/*This function is used to free all the nodes in the trie tree created*/
void free_trie(node *root)
{
    int i;
    if (root != NULL)
    {
        for (i = 0; i < 26; i++)
        {
            free_trie(root->all[i]);
        }
    }

    free(root);
}
