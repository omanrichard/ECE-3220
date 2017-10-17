//
//  lab7.c
//  Lab 7
//
//  Created by Richard Oman on 7/18/16.
//  Copyright © 2016 Richard Oman. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct n_
{
    int num;
    struct n_* left;
    struct n_* right;
} Node;

/* Prototypes */
Node* addNodeToTree( Node* root, int x );
void freeTree( Node* root );
void printSortedList( Node* root );
Node* removeLeaves( Node* root );
Node* flipTree( Node* root );

void printTree(Node* root);
int calcPrint(Node* root, int is_left, int offset, int depth, char s[20][255]);

/* Functions */

Node* addNodeToTree( Node* root, int x )
{
    if( root == NULL )  /* Allocates when root is looking at the appropriate "NULL" location */
    {
        root = malloc( sizeof( Node ) );
        root->num = x;
        root->left = NULL;
        root->right = NULL;
    }
    
    /* Looks for proper location in tree */
    else if( x < root->num )    /* Lower goes to the left */
        root->left = addNodeToTree( root->left , x );
    else if( x > root->num )    /* Greater goes to the right */
        root->right = addNodeToTree( root->right , x );
    
    return root;    /* returns the root address in the tree */
}

void freeTree(Node* root)
{
    if( root == NULL )  /* Base Case, continues until the furthest left/right values are reached */
    {
        return;
    }
    
    /* Frees children before freeing the leaf */
    freeTree( root->left );
    freeTree( root->right );
    
    free( root );
    
}

void printSortedList( Node* root )
{
    if( root == NULL )  /* Base case, returns if node is empty */
        return;
    
    printSortedList( root->left );  /* Looks for furthest left value, will be lowest value */
    
    printf("-> %d ", root->num );
    
    printSortedList( root->right ); /* After lowest left value, will look at the value to the right of it to evaluate a print out */
    
}

Node* removeLeaves( Node* root )    /* Node is a leaf if it's children are both NULL */
{
    if( root->left == NULL && root->right == NULL ) /* Free's Node from the list if it's a leaf */
    {
        free( root );
        return NULL;
    }
    else
    {                               /* Looks left and right to erase other leaves */
        root->left = removeLeaves( root->left ); /* removeLeaves evaluates the node to the left */
        root->right = removeLeaves( root->right );/* removeLeaves evaluates the node to the right */
    }   /* Assign to "root->" so that the root->left/root->right values get updated */
    
    return root;
}

Node* flipTree( Node* root )
{
    Node* temp;
    
    if( root == NULL )
        return NULL;
    else if( root->left != NULL && root->right != NULL )
    {
        temp = root->left;                      /* Stores value of root->left */
        root->left = flipTree( root->right );   /* reassigns root->left with value from root->right */
        root->right = temp;                     /* assigns root->right with vale stored in temp */
    }

    return root;
}

/* Print Tree Functions */
int calcPrint(Node* root, int is_left, int offset, int depth, char s[20][255])
{
    char b[20];
    int width = 5;
    
    if (!root) return 0;
    sprintf(b, "(%03d)", root->num);
    int left  = calcPrint(root->left,  1, offset, depth + 1, s);
    int right = calcPrint(root->right, 0, offset + left + width, depth + 1, s);
    
    int i;
    for (i = 0; i < width; i++)
        s[depth][offset + left + i] = b[i];
    
    if (depth && is_left) {
        for (i = 0; i < width + right; i++)
            s[depth - 1][offset + left + width/2 + i] = '-';
        
        s[depth - 1][offset + left + width/2] = '.';
        
    } else if (depth && !is_left) {
        
        for (i = 0; i < left + width; i++)
            s[depth - 1][offset - width/2 + i] = '-';
        
        s[depth - 1][offset + left + width/2] = '.';
    }
    
    return left + width + right;
}

void printTree(Node* root)
{
    char s[20][255];
    int i;
    for(i = 0; i < 20; i++)
        sprintf(s[i], "%80s", " ");
    
    calcPrint(root, 0, 0, 0, s);
    for(i = 0; i < 20; i++)
    {
        printf("%s\n", s[i]);
    }
}

int main( void )
{
    system("clear");
    
    Node* root = NULL;
    
    while(1)
    {
        printf("1. Add a node\n");
        printf("2. Remove leaves\n");
        printf("3. Flip tree\n");
        printf("(-1 to quit)\n>");
        
        int selection;
        int x;
        scanf("%d", &selection );
        
        if(selection == -1)
        {
            break;
        }
        else if( selection == 1 )
        {
            printf("Enter number to add to the tree: ");
            scanf("%d", &x );
            root = addNodeToTree( root, x );
            system("clear");
            printTree( root );
            printSortedList( root );
            printf("\n");   /* to separate sortedList from the menu */
        }
        else if( selection == 2 )
        {
            root = removeLeaves( root );
            system("clear");
            printTree( root );
            printSortedList( root );
            printf("\n");
        }
        else if( selection == 3 )
        {
            root = flipTree( root );
            system("clear");
            printTree( root );
            printSortedList( root );
            printf("\n");
        }
    }

    freeTree(root);
    return 0;

}
