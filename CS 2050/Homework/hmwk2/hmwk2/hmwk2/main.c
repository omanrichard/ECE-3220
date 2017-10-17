//
//  main.c
//  hmwk2
//
//  Created by Richard Oman on 7/16/16.
//  Copyright © 2016 Richard Oman. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct o_
{
    int ID; //the order number
    int daysInQueue; //the number of days old the order is
    struct o_* nextOrder; //to the next order in the list
} Order;

Order** importLists(char* filename);
void printList(Order* firstOrder);
int updateOrder(int ID, Order** oldList, Order** newList);
int processOldestOrder(Order** firstOrder);
void freeList(Order* list);
int getPriority();

void insert( Order* start, Order* newOrder );

//***********START OF REQUIRED FUNCTIONS***************

Order** importLists(char* filename)
{
    FILE* fptr = fopen( filename, "r" );
    
    Order** orderIndex = malloc( sizeof( Order* ) );
    
    Order* newOrder;
    Order* start;
    
    int ID, queueStatus, listIndex;
    
    if( fptr == NULL ) return NULL;
    
    while( !feof( fptr ) )
    {
        fscanf( fptr, "%d %d %d", &ID, &queueStatus, &listIndex );
        
        newOrder = malloc( sizeof( Order ) );
        
        if( newOrder != NULL )
        {
            newOrder->ID = ID;
            newOrder->daysInQueue = queueStatus;
            newOrder->nextOrder = NULL;
            
            switch( listIndex )
            {
                case 0:
                    start = orderIndex[0];
                    insert( start, newOrder );
                    break;
                    
                case 1:
                    start = orderIndex[1];
                    insert( start, newOrder );
                    break;
                    
                case 2:
                    start = orderIndex[2];
                    insert( start, newOrder );
                    break;
                    
                case 3:
                    start = orderIndex[3];
                    insert( start, newOrder );
                    break;
            }   /* end switch */
        }   /* end if */
    }   /* end while */
    
    fclose( fptr );
    
    return orderIndex;
}

int updateOrder(int ID, Order** oldList, Order** newList)
{
}

int processOldestOrder(Order** firstOrder)
{
}

void printList(Order* firstOrder)
{
}

void freeList(Order* list)
{
}

void insert( Order* start, Order* newOrder )
{
    
}

//*************END OF REQUIRED FUNCTIONS*************

int main(int argc, char** argv)
{
    if(argc != 2)
    {
        printf("Usage: ./a.out <filename>\n");
        return -2;
    }
    
    Order** lists = importLists(argv[1]);
    if(lists == NULL)
    {
        printf("Error reading from %s.\n", argv[1]);
        return -1;
    }
    
    while(1)
    {
        printf("1: print a list\n");
        printf("2: change an order's priority\n");
        printf("3: process oldest order\n");
        printf("4: quit\n>");
        int selection;
        scanf("%d", &selection);
        while(selection < 1 || selection > 4)
        {
            printf("Invalid selection, choose again:\n>");
            scanf("%d", &selection);
        }
        
        if(selection == 1)
        {
            printf("Which list do you want to print out?\n");
            int priority = getPriority();
            printList(lists[priority - 1]);
        }
        else if(selection == 2)
        {
            printf("What is the ID of the order to be changed?\n>");
            int ID;
            scanf("%d", &ID);
            printf("What was the ID's old priority?\n");
            int priority = getPriority();
            
            printf("What is the ID's new priority?\n");
            int newPriority = getPriority();
            
            int ret = updateOrder(ID, &lists[priority - 1], &lists[newPriority - 1]);
            if(ret != ID)
            {
                printf("Error updating order no. %d.\n", ID);
            }
            else
            {
                printf("Order no. %d updated successfully.\n", ID);
            }
        }
        else if(selection == 3)
        {
            printf("Which priority list do you want to process from?\n");
            int priority = getPriority();
            int ret = processOldestOrder(&lists[priority - 1]);
            if(ret != 0)
            {
                printf("Error processing from list %d. Is it empty?\n", priority);
            }
            else
            {
                printf("list %d processed successfully.\n", priority);
            }
        }
        else break;
    }
    
    int i;
    for(i = 0; i < 4; i++)
    {
        freeList(lists[i]);
    }
    
    free(lists);
    return 0;
}

int getPriority()
{
    printf("1: Next day\n");
    printf("2: Business\n");
    printf("3: Standard\n");
    printf("4: Long term\n>");
    int priority;
    scanf("%d", &priority);
    while(priority < 1 || priority > 4)
    {
        printf("Invalid selection, choose again:\n>");
        scanf("%d", &priority);
    }
    
    return priority;
}