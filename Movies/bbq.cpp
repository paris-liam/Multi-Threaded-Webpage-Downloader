/* 
Implementation of a multithreaded HTML downloader.Uses the Bounded Buffer Queue.
Author: Liam Paris
Final Lab 

*/

#include <stdio.h>
#include "bbq.h"
#include <string>
using namespace std;
BBQ::BBQ()
{
	// initialize the sync variables
	lock = PTHREAD_MUTEX_INITIALIZER; 
	itemAdded = PTHREAD_COND_INITIALIZER;
	itemRemoved = PTHREAD_COND_INITIALIZER;
	
	front=nextEmpty=0;
}
	
//insert method, modified to take strings	
void BBQ::insert (string item)
{
	pthread_mutex_lock (&lock);
	while ( (nextEmpty-front) == MAX){
		// wait on itemRemoved condition variable, after release 
		// the lock 
		pthread_cond_wait (&itemRemoved, 
			&lock);
		
		//when the calling thread is woken up, 
		// the lock is acquired again, 
		//check again to see if there is space, hence the while loop
		// (this is due to the Mesa semantics) 
	}
	
	items[nextEmpty % MAX] = item;
	nextEmpty ++;
	pthread_cond_signal (&itemAdded);	
	pthread_mutex_unlock (&lock);
}
//remove function modifyed to handle strings
string BBQ::remove()
{
	string item;

	pthread_mutex_lock (&lock);

	while (front == nextEmpty){
		pthread_cond_wait (&itemAdded,&lock);
	}
	item = items[front % MAX];
	front++;

	pthread_cond_signal (&itemRemoved);
	pthread_mutex_unlock (&lock);

//	printf ("remove %s\n", item);

	return item;
}

