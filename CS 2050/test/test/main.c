//Richard Oman
//raothf
//CS1050
//Lab G
//Homework 4

#include <stdio.h>
#include <stdlib.h>

//Prototypes//

int load_data( char* , int* , float* );

void print_data( int* , float* , int );

int update_data(char* , int* , float* , int );

int highest_amount( float* , int );

int lowest_amount( float* , int );

float average_amount( float* , int );

void write_data( char* , int* , float* , int , int , int , float );

//Main//

int main( int argc , char** argv )
{
    if (argc != 5 )
    {
        printf("\nInsufficient arguments\n");
        return 0;
    }
    
    int n = atoi( argv[2] );
    
    int *accountNum = malloc( sizeof(int) * n );
    float *amount = malloc( sizeof(float) * n );
    
    int size = load_data( argv[1] , accountNum , amount );
    
    if ( size == 0 )
    {
        printf("\nUnable to open the input file\n");
        return 0;
    }
    
    print_data( accountNum , amount , size );
    
    printf("\nUpdated Account Information\n");
    
    int update = update_data( argv[3] , accountNum , amount , size );
    
    //	if ( update != 1 );
    //	{
    //		printf("\nUpdate file could not be found\n");
    //		return 0;
    //	}
    
    int highestIndex = highest_amount( amount , size );
    int lowestIndex = lowest_amount( amount , size );
    float average = average_amount( amount , size );
    
    write_data( argv[4] , accountNum , amount , highestIndex , lowestIndex , size , average );
    
    load_data( argv[4] , accountNum , amount );
    
    print_data( accountNum , amount , size );
    
    printf( "\nThe highest amount is $%.2f in the account number %d", *( amount + highest_amount(amount,size)) , *( accountNum + highest_amount(amount,size) ) );
    printf( "\nThe lowest amount is $%.2f in the account number %d", *( amount + lowest_amount(amount,size) ) , *( accountNum + lowest_amount(amount,size) ) );
    printf( "\nThe average amount is $%.2f", average_amount(amount,size) );
    printf( "\n\n" );
    
    free( accountNum );
    free( amount );
    
    return 0;
}


//Functions//
int load_data( char* input , int* accountNum , float* amount )
{
    int i=0;
    
    FILE* loadPTR = fopen( input , "r" );
    
    if ( loadPTR == NULL )
        return 0;
    
    int size;
    
    fscanf( loadPTR , "%d" , &size);
    
    for ( i=0 ; i < size ; i++ )
    {
        fscanf( loadPTR , "%d" , (accountNum + i) );
        fscanf( loadPTR , "%f" , (amount +i) );
    }
    
    fclose( loadPTR );
    
    return size;
}

void print_data( int* accountNum , float* amount , int size )
{
    int i;
    
    printf("\n%11s%10s", "Account No.", "Amount");
    
    for ( i=0 ; i < size ; i++ )
    {
        printf("\n%11d%10.2f", *(accountNum + i) , *(amount + i));
    }
    
    printf("\n");
}

int update_data(char* update , int* accountNum , float* amount , int size )
{
    int i;
    int j;
    
    FILE* updatePTR = fopen( update , "r" );
    
    if ( updatePTR == NULL )
        return 0;
    
    int updateSize;
    
    fscanf( updatePTR , "%d" , &updateSize);
    
    int *accountNum2 = malloc(sizeof(int)*updateSize);
    float *amount2 = malloc(sizeof(float)*updateSize);
    
    for ( i=0 ; i<size ; i++)
    {
        fscanf( updatePTR , "%d" , (accountNum2 + i) );
        fscanf( updatePTR , "%f" , (amount2 +i) );
    }
    
    for ( j=0 ; j<4 ; j++ )
    {
        for ( i=0 ; i<size ; i++ )
        {
            if ( *(accountNum + i) == *(accountNum2 + j) )
                *(amount + i) = ( *(amount2 + j) + *(amount + i));
        }
    }
    
    fclose( updatePTR );
    
    free( accountNum2 );
    free( amount2 );
    
    return 1;
}

int highest_amount( float* amount , int size )
{
    int i;
    int index=0;
    
    for ( i=0 ; i < (size-1) ; i++ )
    {
        if( *(amount + i) <= *( amount + index ))
            index = index;
        else
            index = i;
    }
    
    return index;
}

int lowest_amount( float* amount , int size )
{
    int i;
    int index=0;
    
    for ( i=0 ; i< (size-1) ; i++ )
    {
        if( *(amount + i) >= *( amount + index ) )
            index = index;
        else
            index = i;
    }
    
    return index;
}

float average_amount( float* amount , int size )
{
    int i;
    float sum = 0;
    float average;
    
    for ( i=0 ; i<size ; i++ )
        sum += *(amount + i);
    
    average = sum / size;
    
    return average;
}

void write_data( char* output , int* accountNum , float* amount , int highest , int lowest , int size  , float average )
{
    FILE *outputPTR = fopen( output , "w" );
    
    int i;
    
    fprintf( outputPTR , "\n%11s%10s\n", "Account No.", "Amount");
    
    for ( i=0 ; i < size ; i++ )
    {
        fprintf( outputPTR , "%11d%10.2f\n", *(accountNum + i) , *(amount + i));
    }
    
    fprintf( outputPTR , "\nThe highest amount is $%.2f in the account number %d", *(amount + highest) , *(accountNum + highest) );
    fprintf( outputPTR , "\nThe lowest amount is $%.2f in the account number %d", *(amount + lowest) , *(accountNum + lowest) );
    fprintf( outputPTR , "\nThe average amount is $%.2f", average );
    
    fclose( outputPTR );
}


