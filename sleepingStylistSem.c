//===sleepingStylistSem.c=============//
//Imports
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define CHAIRS 7
#define DELAY 1000000  //adjust this value
#define STYLIST 1
#define CUSTOMER 120

//Mutual extension
sem_t mutex;
//Number of stylist waiting for customers 
sem_t stylist;
//Number of waiting for service
sem_t customers;

//Define Thread
pthread_t stylistThread;
pthread_t customerThread[CUSTOMER];

//Customer waiting
int waiting = 0;

int customerServed = 0;

void *stylist_func( void *stylistId );
void *customer( void *customerId );

int main()
{   
    //Initialize semaphore
    sem_init( &mutex, 0 , 1);
    sem_init( &stylist, 0, 0);
    sem_init( &customers, 0, 0);

    //Stylist
    pthread_create( &stylistThread, NULL, (void *)stylist_func, NULL );

    int i;
    //Customer
    for(i=0; i < CUSTOMER; i++){
        pthread_create( &customerThread[i], NULL, (void *)customer, i );
    }

    int j;
    for(j=0; j< CUSTOMER; j++){
        pthread_join( customerThread[j], NULL );
    }
   // pthread_join( stylistThread, NULL );
    printf("Total customer served today: %d\n", customerServed++);
    return 0;
}

void *stylist_func( void *stylistId )
{
    int j;
    while (1)
    {
        
        sem_wait( &customers ); //stylist go to sleep if customer is 0
        sem_wait( &mutex ); //Acquire access for waiting
        waiting = waiting - 1;  //decreament count of waiting customer
        printf("Stylist is serving a Customer\n");
        sem_post( &stylist ); // stylist is ready to cut hairs
        sem_post( &mutex ); //release waiting
        for( j=0; j<DELAY; j++ ); //cut hair
	customerServed++;
        
    }
}

void *customer( void *tempCustomerId )
{
    int customerId = ( int* )tempCustomerId;
    int j;
    while(1)
    {
        sem_wait(&mutex);
        if( waiting < CHAIRS )
        {   
            printf("Customer %d is waiting in chair\n", customerId);
            waiting = waiting + 1;
            sem_post( &customers );
            sem_post( &mutex );  
            sem_wait( &stylist );
            break;

        }else{
            sem_post( &mutex );
            for( j=0; j<DELAY ; j++); //go shopping
            //printf("Customer %d went for shopping \n", customerId);

        }
    }
}
