Sleeping stylist with Semaphore 
-------------------------------

####__Rules:__
1. One stylist &rarr; one customer
2. No customer &rarr; stylist sleeps 
3. Customer wakes up stylist &rarr; stylist gets ready
4. Stylist busy  &rarr; Customer sits on chair ( queue )
5. Chairs full &rarr; Customer go to mall &rarr; comeback later ( suspend )
6. Every customer should get haircut( Task must be completed )
7. Customer must be taken form queue
8. If queue is empty stylist must go to sleep 

####__TODOS:__ 
1. Use pthread library to create 120 threads & 1 stylist thread 
2. Add delay to slow down each thread adjust loop bound to get steady stream of customers
3. Demonstrate or show the operations when its full, not full or empty
4. See the gradual build up of customer waiting in chairs

