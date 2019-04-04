#include<stdio.h>
#include<semaphore.h>

#define CHAIRS 7
#define EMPTY 0
#define OCCUIPIED 1 
#define DELAY 10000000

typedef struct{
    int noOfThreadBlocked;
    sem_t suspendThread;
}cond;

cond stylistAvailable, customerAvailable;

int customer = 0;
int stylist = 0;

int givenHaircuts = 0; 
int salonFull = 0;
int salonEmpty = 0;

int customerQueue[CHAIRS];

sem_t mutex;

void mon_init()
{
    sem_init( &mutex, 0, 1 );
    sem_init( &(stylistAvailable.suspendThread), 0, 0);
    sem_init( &(customerAvailable.suspendThread), 0, 0);
    customerAvailable.noOfThreadBlocked = 0;
    stylistAvailable.noOfThreadBlocked = 0;
}

void mon_wait(cond *cv)
{
    cv->noOfThreadBlocked++;
    sem_post( &mutex );
    sem_wait( &(cv->suspendThread)); 
}

void mon_signal(cond *cv)
{
    if(count(cv) == 0)
        sem_post( &mutex );
    else
    {
        cv->noOfThreadBlocked--;
        sem_post( &(cv->suspendThread) );
    } 
}

int count(cond *cv) { return cv->noOfThreadBlocked; }

void mon_checkCustomer()
{   
    sem_wait( &mutex );

    stylist++;
    mon_signal( &stylistAvailable );
    
    if( customer == 0)
        mon_wait( &customerAvailable );
    customer--;
    givenHaircuts++;
    sem_post( &mutex );

}

int mon_checkStylist()
{
    sem_wait( &mutex );

    int status = 0;
    if( customer < CHAIRS )
    {
        customer++;
        mon_signal( &customerAvailable);
        if( stylist == 0)
            mon_wait( &stylistAvailable );
        stylist--;
        status = 1;
    }
    sem_post( &mutex );
    return status;
}

void mon_debugPrint()
{
    sem_wait( &mutex );

    if( customer == EMPTY )
        salonEmpty++;
    if( customer == CHAIRS )
        salonFull++;
    
    int i;
    for( i=0; i<CHAIRS; i++)
        customerQueue[i] = EMPTY;
    int j;
    for( j=0; j<customer; j++ )
        customerQueue[j] = OCCUIPIED;

    printf("Customer queue: %d|%d|%d|%d|%d|%d|%d => Total = %d \n", 
            customerQueue[0], customerQueue[1], customerQueue[2], customerQueue[3],
            customerQueue[4], customerQueue[5], customerQueue[6], customer);
    printf("Given Haircuts = %d \n", givenHaircuts);
    printf("Salon full = %d times\n", salonFull);
    printf("Salon empty = %d times\n", salonEmpty);
    printf("============================================\n");
    
    sem_post( &mutex );
    
}