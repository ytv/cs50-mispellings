/* ***********
 * by ytv
 * CS50x
 * uses a trie
 /

/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

typedef struct node
{
    struct node* letter[27];
    bool end_of_word;
} node;

// create the root table
struct node* root;

int word_count = 0;

bool free_funct(struct node* node);

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    bool found = true;
    int z = strlen(word), i = 0;
    node* cursor = root;
    
    char temp_2[LENGTH+1];
    strcpy(temp_2, word);
        
    for(int i = 0; i < z; i++)
    {
        temp_2[i] = tolower(temp_2[i]);
    }
    
    
    do{
        int index = temp_2[i] - 'a';
        
        if(cursor->letter[index] == NULL)
        {
            found = false;
        }
        else
        {
            cursor = cursor->letter[index];

            if(i == z - 1)
            {
                if(cursor->end_of_word == false)
                {
                    found = false;
                }
            }
            
            i++;
        }
        
    }while(i < z && found == true);
  
    return found;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    root = calloc(1, sizeof(node));
    
    // create new_node and load in word
    FILE* fp;
    fp = fopen(dictionary, "r");
       
    if (!fp)
    {
        printf("Error: unable to open dictionary file\n");
        return false; 
    }
    else
    {
        struct node* cursor;
        char temp_1[LENGTH+1];
        
        while(fscanf(fp, "%s", temp_1) != EOF)
        {            
            word_count++;
            
            int len = strlen(temp_1);

            cursor = root;
            
            for(int index = 0; index <= len; index++)
            {
                if(index == len)
                {
                    cursor->end_of_word = true;
                }
                else
                {
                    int k = temp_1[index] - 'a';
                    
                    //if letter[k] is pointing to something, go to it
                    //otherwise, create a new node and then point to it
                    if(cursor->letter[k] != NULL)
                    {
                        cursor = cursor->letter[k];
                    }
                    else
                    {
                        node* new_node = calloc(1, sizeof(node));
                        new_node->end_of_word = false;
                        
                        cursor->letter[k] = new_node;
                        cursor = cursor->letter[k];
                    }
                }
            }
        }
    }
    fclose(fp);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return word_count;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    return free_funct(root);
}

bool free_funct(struct node* node)
{
    int i = 0;
    
    while(i < 27)
    {
        if(node->letter[i] != NULL)
        {
            free_funct(node->letter[i]); 
        }
        i++;
    }
    
    free(node);
    
    return true;
}
