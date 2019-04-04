#include <semaphore.h>
#define monitor_h

typedef struct{
    int noOfThreadBlocked;
    sem_t suspendThread;
}cond;

extern void mon_init();
extern void mon_signal(cond *);
extern void mon_wait(cond *);
extern void mon_checkCustomer();
extern int mon_checkStylist();
extern void mon_debugPrint();
