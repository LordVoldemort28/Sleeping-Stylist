//===== sleepingStylistMon.c ========//
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include "monitor.h"

#define CHAIRS 7
#define DELAY 1000000  //adjust this value
#define STYLIST 1
#define CUSTOMER 120

//Define Thread
pthread_t stylistThread;
pthread_t customerThread[CUSTOMER];

void *stylist_func( void *stylistId );
void *customer_func( void *customerId );

void main( void )
{
    //Create a specified number of customer thread 
    //and a stylist thread. Don't forget to join thread
    mon_init();

    //Stylist
    pthread_create( &stylistThread, NULL, (void *)stylist_func, NULL );

    int i;
    //Customer
    for(i=0; i < CUSTOMER; i++){
        pthread_create( &customerThread[i], NULL, (void *)customer_func, i );
    }

    int j;
    for(j=0; j< CUSTOMER; j++){
        pthread_join( customerThread[j], NULL );
    }

    pthread_join( stylistThread, NULL);
}

void *stylist_func( void *stylistId )
{
    int j;
    while(1)
    {
        mon_debugPrint();
        mon_checkCustomer();
        for( j=0; j<DELAY; j++);
    }
}

void *customer_func( void *customerId )
{
    int pid = (*int) customerId;
    //add more variable as needed
    int j;
    while(1)
    {
        mon_debugPrint();
        if( mon_checkStylist() )
            break;
        for( j=0; j<DELAY; j++); //go shopping
        
    }   
}