//===sleepingStylistSem.c=============//
#define CHAIRS 7
#define DELAY 1000000  //adjust this value
#define STYLIST 1
#define CUSTOMER 120

/*
1. one stylist ---> one customer
2. No customer ----> stylist sleeps 
3. Customer wakes up stylist ---> stylist gets ready
4. Stylist busy  ----> Customer sits on chair ( queue )
5. Chairs full ----> Customer go to mall ---> comeback later (suspend)
6. Every customer should get haircut( Task must be completed )
7. Customer must be taken form queue
8. If queue is empty stylist must go to sleep 
**/

typedef int semaphore;

//Mutual extension
semaphore mutex = 1;
//#Number of stylist waiting for customers 
semaphore stylist = 0;
//Number of waiting for service
semaphore customers = 0;

//Customer waiting
int waiting = 0;

void main( void )
{
    //Create a specified number of customer thread 
    //and a stylist thread. Don't forget to join thread
}

void stylist( void )
{
    int j;
    while (1)
    {
        
        down( &customers ); //stylist go to sleep if customer is 0
        down( &mutex ); //Acquire access for waiting
        waiting = waiting - 1  //decreament count of waiting customer 
        up( &stylist ); // stylist is ready to cut hairs
        up( &mutex ); //release waiting
        for( j=0; j<DELAY; j++ ); //cut hair

    }
}

void customer( void )
{
    int j;
    while(1)
    {
        down(&mutex);
        if( waiting < CHAIRS )
        {
            waiting = waiting + 1;
            up( &customers );
            up( &mutex );  
            down( &stylist )
            break;
        }else{
            up( &mutex );
            for( j=0; j<DELAY ; j++); //go shopping  
        }
    }
}