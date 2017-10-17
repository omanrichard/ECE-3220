//
//  main.c
//  cool
//
//  Created by Richard Oman on 3/20/17.
//  Copyright © 2017 Richard Oman. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
 DEFINITIONS
 */

typedef struct Book{
    int bookID;
    char* title;
    bool checkedOut;
    struct Book* next;
}book;

typedef struct BookIds{
    int id;
    struct BookIds* next;
}bookIds;

typedef struct Student{
    char* firstName;
    char* lastName;
    int priority;
    int readingLevel;
    bookIds* wishlist;
    struct Student* next;
}student;

#define NAME 25
#define TITLE 50

/*
 PROTOTYPES 
 */

//Part One
student* buildStudentList(char* studentsFile, student* head);
void printStudents(student* head);
void createPriorityQueue(student* head);

//Part Two
void addWishlist(student* head,char* wishListfile);
book* createBookList(char* bookFile,book* bookHead);
void printBookList(book* bookHead);

//Part Three
void checkOutBooks(student* studentHead, book* bookHead);
book* findBook(book* bookhead, int book_id);

/*
 MAIN
 */

int main(int argc, char* argv[]){
    
    student* head = NULL;
    
    if( argc != 4 )
    {
        printf("Usage: ./a.out <students.txt> <wishlist.txt> <books.txt>");
        return -2;
    }
    
    head = buildStudentList(argv[1], head);
    
    return 0;
}


/* 
 FUNCTIONS 
 */

/* Build Lists */

student* buildStudentList(char* studentsFile, student* head) {
    
    FILE* fptr = fopen( studentsFile, "r");
    
    student* current = head;
    student* previousPtr = NULL;
    
    /*Revisit*/
    if( fptr == NULL ){
        printf("Error: File could not be opened\n\n");
        return 0;
    }
    
    while( !feof( fptr ))
    {
        if( current == head )
        {
            current = malloc( sizeof(student)); /* Allocating space for first student information */
        
            fscanf( fptr, "%s %s %d %d", current->firstName, current->lastName, &current->priority, &current->readingLevel ); /* Assigning read values to Allocated space */
            
            current->next = NULL; /* Initialize next student to zero */
            
            previousPtr = current;  /* Stores the address of the head */
            head = current;
            current = NULL; /* Breaks if statement */
        }
        
        else
        {
            current = malloc( sizeof( student ));   /* Initializes memory for next student */
            
            previousPtr->next = current;    /* THIS IS WHERE LINKING HAPPENS */
        
            fscanf( fptr, "%s %s %d %d", current->firstName, current->lastName, &current->priority, &current->readingLevel );
            
            previousPtr = current;
            
            current->next = NULL;
        }
        
    }
    return head;
}

/* Print Lists */

void printStudents(student* head) {
    
    student* current = head;
    
    if(head == NULL)
        printf("The head was NULL\n\n");
    
    while( current != NULL )
    {
        printf("/nFirst Name: %s\nLast Name: %s\nPriority: %d\nReading Level: %d\n", current->firstName, current->lastName, current->priority, current->readingLevel);
        current = current->next;
    }
}

/* Create Priority*/

void createPriorityQueue(student* head) {
    
    student* queue = NULL;
    student* current = head;
    student* newPtr = NULL;
    student* queueHead = NULL;
    student* hold = NULL;
    
    int queueCount = 0;
    int i=0;
    int j=0;
    
    queue = malloc( sizeof(student));
    
    /*Copies List to sort into a queue*/
    while( current != NULL )
    {
        
        
        queue->firstName = current->firstName;
        queue->lastName = current->lastName;
        queue->priority = current->priority;
        queue->readingLevel = current->readingLevel;
        
        current = current->next;
        
        if( current == NULL)
            queue->next = NULL;
        
        else
        {
            newPtr = malloc( sizeof(student));
            queue->next= newPtr;
        
            queue = queue->next;
        }
        
        queueCount++;
    }
    
    /*Lets sort Queue*//*Head needs to be lowest priority*/
    queueHead = queue;
    
    for(i=0; i<queueCount; i++)
    {
        for(j=0; j<queueCount; j++)
        {
            
        }
        
    }
    
    
}

void addWishlist(student* head,char* wishListfile) {
    
}
book* createBookList(char* bookFile,book* bookHead) {
    return NULL;
}
void printBookList(book* bookHead) {
    
}

void checkOutBooks(student* studentHead, book* bookHead) {
    
}
book* findBook(book* bookhead, int book_id) {
    return NULL;
}
