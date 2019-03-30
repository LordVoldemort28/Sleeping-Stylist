Sleeping stylist with Semaphore 
-------------------------------

__Rules:__
* One stylist &rarr; one customer
* No customer &rarr; stylist sleeps 
* Customer wakes up stylist &rarr; stylist gets ready
* Stylist busy  &rarr; Customer sits on chair ( queue )
* Chairs full &rarr; Customer go to mall &rarr; comeback later ( suspend )
* Every customer should get haircut( Task must be completed )
* Customer must be taken form queue
* If queue is empty stylist must go to sleep 

__TODOS:__ 
* Use pthread library to create 120 threads & 1 stylist thread 
* Add delay to slow down each thread adjust loop bound to get steady stream of customers
* Demonstrate or show the operations when its full, not full or empty
* See the gradual build up of customer waiting in chairs

Sleeping stylist with Monitor
------------------------------

__Give synchronization support to sleeping stylist__

* Can't use pthread library for conditional variables 
* CV are used to suspend process or thread 
* Create the variables type CV and name that struct called "cond"
* Structure consist of int variables that indicates the # of thread blocked on a conditional
variable and semaphores used to suspend thread ( signal and wait )
* Implementation shouldn't follow the signal-continue
* CV will support 
    * count( cv ) &rarr; Return number of threads blocked 
    * wait( cv )  &rarr; Give up exclusive access to monitor then suspends the executing thread
    * signal( cv ) &rarr; The signal thread resume execution where it was last suspended  