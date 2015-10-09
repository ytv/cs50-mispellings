// uses hash function
// prints misspelled words exactly how they appear in the text

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
    char word[LENGTH + 1];
    struct node* next;
} node;

// create a hash table
struct node* hash[26] = {NULL};

int word_count = 0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    int j = tolower(word[0])-'a';
    
    bool found = false, eo_list = false;
    
    node* cursor = hash[j];
    
    if(cursor == NULL)
    {
        return false;
    }
    else
    {
        // make the word completely undercase
        
        int z = strlen(word);
        char low_case_word[z];
        strcpy(low_case_word, word);
        
        for(int i = 0; i < z; i++)
        {
            low_case_word[i] = tolower(low_case_word[i]);
        }
        
        //sanity check
        //printf("after using tolower, the word is %s\n", word);
        
        do
        {
            if(strcmp(cursor->word, low_case_word) == 0)
                found = true;
            else
            {
                if(cursor->next != NULL)
                    cursor = cursor->next;
                else
                    eo_list = true;
            }
        } while((found == false) && (eo_list == false));
    
        return found;
    }
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // open up the dictionary file
    FILE* fp;
    fp = fopen(dictionary, "r");
    
    if (!fp)
    {
        printf("Error: unable to open dictionary file\n");
        return false; //update  
    }
    else
    {
        char temp_1[LENGTH+1];
        
        while(fscanf(fp, "%s", temp_1) != EOF)
        {
            word_count++;
           // printf("%s\n", temp_1);
            
            // create new node and load in the new word from dictionary into the new_node    
            node* new_node = malloc(sizeof(node));
            new_node->next = NULL;
            strcpy(new_node->word, temp_1);
            
            char c = new_node->word[0];
            int k = c - 'a';
           // printf("%i\n", k);
            
            // check if hash[k] is already pointing to a node or not
            // if no, assign hash[k] to point to new node
            // if yes, traverse the hash[k] linked list until it finds its end and append to the end
            if(hash[k] == NULL)
            {
                
                hash[k] = new_node;
            }
            else
            {
                node* temp_2 = hash[k];
                
                while(temp_2->next != NULL)
                {
                    temp_2 = temp_2->next;
                }
                temp_2->next = new_node;
            }
        }
    }
   
    // sanity check to make sure all words were loaded
    /*for(int i = 0; i < 26; i++)
    {
        printf("hash[%c]: ", i + 'a');
        
        node* node_to_print = hash[i];
        while(node_to_print != NULL){
            printf("%s -> ", node_to_print->word);
            node_to_print = node_to_print->next;
        }
        printf("\n");
    }*/

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
    for(int i = 0; i < 26; i++)
    {
        //free_func(hash[i]);
        struct node* cursor_2 = hash[i];
        struct node* to_free;
        
        while((to_free = cursor_2) != NULL)
        {
            cursor_2 = cursor_2->next;
            free(to_free);
        }
    }
    
    return true;
}
