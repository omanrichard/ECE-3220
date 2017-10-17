//
//  main.c
//  Lab 8
//
//  Created by Richard Oman on 7/25/16.
//  Copyright © 2016 Richard Oman. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXLINELENGTH 100

/* Prototypes */
bool isATime(char* string);
bool isADate(char* string);
bool isAPhoneNumber(char* string);

/* Main */
int main(int argc, char** argv)
{
    if(argc != 2)
    {
        printf("Usage: ./a.out <filename>\n");
        exit(-1);
    }
    
    FILE* fp = fopen(argv[1], "r");
    if(!fp)
    {
        printf("Could not open %s. Is the file okay?\n", argv[1]);
        exit(-1);
    }
    
    char* tmp = malloc(sizeof(char)*MAXLINELENGTH);
    while(fgets(tmp, MAXLINELENGTH, fp) != NULL)
    {
        char* p;
        
        p = tmp;
        
        if(isATime(tmp))
        {
            printf("%s is a time.\n", p);
        }
        if(isADate(tmp))
        {
            printf("%s is a date.\n", tmp);
        }
        if(isAPhoneNumber(tmp))
        {
            printf("%s is a phone number.\n", p);
        }
    }
    
    fclose(fp);
    free(tmp);
    
    return 0;
}

/* Functions */
bool isATime(char* string)
{
    return false;
}

bool isADate(char* string)
{
    char* p = string;
    char* tokenMonth = NULL;
    char* tokenDay = NULL;
    char* tokenYear = NULL;
    
//    char Month, Day, Year;
    int temp;
    
    const char t[2]= "/";   /* Token terminator */
    
    /* Date: first/second/third */
    tokenMonth = strtok( p , t );   /* Gets first token from string */
    tokenDay = strtok( NULL , t );  /* Gets second token from string */
    tokenYear = strtok( NULL , t ); /* Gets third token from string */
    
    
    //Month = *tokenMonth;
    
    if( tokenDay == NULL )
            return false;
    
    //Day = *tokenDay;
    
    if( tokenYear ==NULL )
        return false;
    
    //Year = *tokenYear;
    
    /****************/
        temp = atoi( tokenMonth );
    
        if( temp < 1 || temp > 12 ) /* Checks Month is between 1-12, return false if out of range */
            return false;
    
        temp = atoi( tokenDay );
    
        if( temp < 1 || temp > 31 ) /* Checks Day is between 1-31, return false if out of range */
            return false;
    
        temp = atoi( tokenYear );
    
        if( temp < 1969 )           /* Checks year is above lowest value accepted, return false if less than */
        return false;
    return true;
}

bool isAPhoneNumber(char* string)
{
    char* p = string;
    char* tokenArea = NULL;
    char* tokenFirst = NULL;
    char* tokenSecond = NULL;
    
    const char t[2]= "-";   /* Token terminator */
    const char n[2]= "\n";
    /* Phone No.: Area-First-Second */
    tokenArea = strtok( p , t );        /* gets Area token */
    tokenFirst = strtok( NULL , t );    /* gets First token */
    tokenSecond = strtok( NULL , n );   /* gets Second token */
    
    /* Verify Area Token */
    if( strlen( tokenArea ) != 3 )      /* Checks Area is 3 char long */
        return false;
    
    else if( atoi(tokenArea) <= 0 || atoi(tokenArea) > 999 )  /* Checks Area is between 1-999 */
            return false;
    
    
    /* Verify First Token */
    if( strlen( tokenFirst ) != 3 ) /* Checks First is 3 char long */
        return false;
    
    else if( atoi(tokenFirst) < 0 || atoi(tokenFirst) > 999 )  /* Checks First is between 0-999 */
            return false;
    
    /* Verify Second Token */
    if( strlen( tokenSecond ) != 4 )    /* Checks Second is 4 char long */
        return false;
    
    else if( atoi(tokenSecond) <= 0 || atoi(tokenSecond) > 9999 )  /* Checks Second is between 1-999 */
            return false;
    
    return true;
}





