
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"
int count = 1;
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
void print_it(node *root, char str[], int level)
{
    if (root->isLeafNode)
    {
        str[level] = '\0';
        printf("%s\n", str);
    }
    int i;
    for (i = 0; i < 26; i++)
    {
        if (root->all[i])
        {
            str[level] = i + 'a';
            print_it(root->all[i], str, level + 1);
        }
    }
}
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
    int last = last_node(temp);         //prefix is last node of a tree
    if (word && last)
    {
        return -1;
    }
    if (!last)
    {
        count = 0;
        rec_sug(temp, str);
    }
}

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
void user_input(node *root)
{
    FILE *fp;
    char *c;
    char sug[20];
    char str[200];
    int i = 0,j,l, sug_out,error_out=0;

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