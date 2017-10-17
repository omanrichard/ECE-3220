//
//  main.c
//  HW3
//
//  Created by Richard Oman on 7/18/16.
//  Copyright © 2016 Richard Oman. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
//HINT: you'll be using this!
#include <string.h>

#define MAXCITYNAME 30
#define MAXLINELENGTH 50

typedef struct n_
{
    int zipCode; //A zip code that exists in the given city/state
    char* city; //Will point to a city name
    char state[3]; //A state abbreviation. Note that we need
    //room for the NULL terminator!
    struct n_* left; //connections to other nodes
    struct n_* right;
} Node;

/* Prototypes */
Node* importTree(char* filename);
Node* addNode(Node* root, Node* newNode);
int findStateCount(Node* root, char* state);
Node* findZipCode(Node* root, int zipCode);
void freeTree(Node* root);
void printMenu();

/* Main */
int main(int argc, char** argv)
{
    Node* nodeIndex = NULL;
    Node* zipCode = NULL;

    if( argc != 2 )
    {
        printf("Usage: ./a.out <filename>\n");
        return -2;
    }   /* end if */
    
    nodeIndex = importTree( argv[1] );
    
    int selection;
    
    printMenu();
    scanf("%d", &selection );
    
    while( selection < 1 || selection >3 )
    {
        printf("Invalid selection, choose again:\n> ");
        scanf("%d", &selection );
    }   /* end while */
    
    while( selection != 3 )
    {
        while( selection < 1 || selection >3 )
        {
            printf("Invalid selection, choose again:\n> ");
            scanf("%d", &selection );
        }
        
        switch( selection )
        {
            case 1:
            {
                char state[3];
                printf("Enter the state you want to search for:\n> ");
                scanf("%s", state );
                printf("The state has %d results in the sample\n", findStateCount( nodeIndex , state ));
                break;
            }
                
            case 2:
            {
                int zip = 0;
                printf("Enter the zip code you want to find:\n> ");
                scanf("%d", &zip );
                
                zipCode = findZipCode( nodeIndex , zip );
            
                if( zipCode == NULL )
                {
                    printf("No results foud for %d\n", zip );
                    break;
                }
                else
                {
                    printf("Result found for %d:\n"
                           "City: %s\n"
                           "State: %s\n", zip, zipCode->city, zipCode->state );
                    break;
                }
            }
        }   /* end switch */
        
        printMenu();
        scanf("%d", &selection );
    }   /* end while */
    
    freeTree( nodeIndex );
    return 0;
}

/* Functions */
Node* addNode(Node* root, Node* newNode)
{
    if( root == NULL ){
        root = newNode;
        return root;
    }
    
    else if( newNode->zipCode < root->zipCode ) /* Lower goes to left */
        root->left = addNode( root->left , newNode );
    else if( newNode->zipCode > root->zipCode ) /* Higher goes to right */
        root->right = addNode( root-> right , newNode );
    
    return root;
}

int findStateCount(Node* root, char* state)
{
        int count = 0;

        if (root != NULL)
        {
            if (strcmp((root-> state), (state)) == 0)
                ++count;
            
            count += findStateCount(root->left, state);
            
            count += findStateCount(root->right, state);
        }
        return count;
}

Node* findZipCode(Node* root, int zip)
{
    if( root == NULL )
    {
        return root;
    }
    else if( root->zipCode == zip )
        return root;
    else if( zip < root->zipCode )
        return findZipCode( root->left , zip );
    else
        return findZipCode( root->right , zip );
}

void freeTree(Node* root)
{
    if( root == NULL )  /* Base Case, continues until the furthest left/right values are reached */
    {
        free(root);
        return;
    }
    
    /* Frees children before freeing the leaf */
    freeTree( root->left );
    freeTree( root->right );
    
    free( root->city );
    free( root );
}

Node* importTree(char* filename)
{
    Node* root = NULL;  /* Initializes value for root */
    
    FILE* fp = fopen(filename, "r");    /* opens input file, fp = the address of file */
    
    if(!fp) /* error check for if the file is not opened properly or not at all */
    {
        printf("Error opening file.\n");
        return NULL;
    }
    
    while(!feof(fp))    /* while loop breaks when feof reaches the end of the file */
    {
        Node* new = malloc(sizeof(Node));   /* allocates memory for a new node */
        if(!new)    /* error check for if malloc fails */
        {
            printf("Failed to allocate memory. Ending read.\n");
            exit(1);
        }
        new->city = malloc(sizeof(char)*MAXCITYNAME);
        if(!(new->city))
        {
            printf("Failed to allocate memory. Ending read.\n");
            exit(1);
        }
        new->left = NULL;
        new->right = NULL;
        char* line = malloc(sizeof(char)*MAXLINELENGTH);
        if(!line)
        {
            printf("Failed to allocate memory. Ending read.\n");
            exit(1);
        }
        if(fgets(line, MAXLINELENGTH, fp) == NULL)
        {
            if(!feof(fp))
            {
                printf("File reading ended prematurely. Check for errors in the file.\n");
                exit(1);
            }
            free(new->city);
            free(line);
            free(new);
            fclose(fp);
            break;
        }
        char* tmp = strtok(line, ",");
        new->zipCode = atoi(tmp);
        tmp = strtok(NULL, ",");
        strcpy(new->city, tmp);
        new->city[strlen(tmp)+1] = '\0';
        tmp = strtok(NULL, "\n");
        strcpy(new->state, tmp);
        new->state[2] = '\0';
        root = addNode(root, new);
        if(!root)
        {
            printf("Root of tree is still NULL! Ending read.\n");
            exit(1);
        }
        free(line);
    }

    return root;
}

void printMenu()
{
    printf("1: Find number in a state\n"
           "2: Find a zip code\n"
           "3: Exit\n"
           "> ");
}



