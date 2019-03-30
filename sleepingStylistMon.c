//===== sleepingStylistMon.c ========//
#define DELAY 1000000 //adjust this value

void main( void )
{
    //Create a specified number of customer thread 
    //and a stylist thread. Don't forget to join thread
}

void stylist( void )
{
    //add more variable as needed
    int j;
    while (1)
    {
        mon.debugPrint();
        mon.checkCustomer();
        for( j=0; j<DELAY; j++); //cut hair
    }
}

void customer( void )
{
    //add more variable as needed
    int j;
    while(1)
    {
        mon.debugPrint();
        if( mon.checkStylist() )
            break;
        for( j=0; j<DELAY; j++); //go shopping
    }   
}