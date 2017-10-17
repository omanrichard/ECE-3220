//
//  main.c
//  prelab7
//
//  Created by Richard Oman on 7/18/16.
//  Copyright © 2016 Richard Oman. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

//Your structure.
typedef struct n_
{
    int num;
    struct n_* left;
    struct n_* right;
} Node;

//Your prototypes
Node* addNodeToTree(Node* root, int x);
void printTree(Node* root);
int calcPrint(Node* root, int is_left, int offset, int depth, char s[20][255]);
void freeTree(Node* root);

//Your main
int main(void)
{
    //this clears the screen. Useful!
    system("clear");
    //Keeps track of the root of the tree at all times.
    Node* root = NULL;
    while(1)
    {
        //There can be better ways to do this so that
        //-1 can get in the tree if needed, but we're
        //keeping it simple.
        printf("Add a node (-1 to quit): ");
        int x;
        scanf("%d", &x);
        
        if(x == -1)
        {
            break;
        }
        else
        {
            //Just like we need the start of a linked
            //list at all times, we need the root of the
            //tree at all times.
            root = addNodeToTree(root, x);
            system("clear");
            //A decent way to print out the tree. NOTES ON THE PRINT:
            //1.	I did not come up with the printing code.
            //		Got it on the internet.
            //2.	The print can support 20 levels deep and roughly
            //		10 nodes wide. Keep the tree small when testing.
            //3.	The above statement is true on a screen that can do
            //		1920x1080. Only smaller trees will be supported on
            //		smaller screens.
            printTree(root);
        }
    }
    
    //Free it all up
    freeTree(root);
    return 0;
}

//COMPLETE ME
Node* addNodeToTree(Node* root, int x)
{
    
    if( root == NULL )
    {
        root = malloc( sizeof( Node ) );
        root->num = x;
        root->left = NULL;
        root->right = NULL;
    }
    
    else if( x < root->num )
        root->left = addNodeToTree(root->left, x );
    else if( x > root->num )
    {
        root->right = addNodeToTree( root->right, x );
        return root;
    }
    //Remember the questions that you have to ask:
    //	Am I at a place where I can put a node? (base case)
    //	Should I look left or right for a place to put the node?
    //	What is the root of the tree RELATIVE TO THE RECURSIVE CALL?
    //		(that question helps with handling function returns)
    //	Is the number that I'm adding already in the tree? Is that okay?
}

//COMPLETE ME TOO
void freeTree(Node* root)
{
    if( root == NULL )
    {
        return;
    }
    
    freeTree( root->left );
    freeTree( root->right );
    
    free( root );
    
}

//DON'T TOUCH UNLESS YOU WANT TO EXPERIMENT
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

//SAME AS THE FUNCTION ABOVE
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