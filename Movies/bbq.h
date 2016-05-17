/* define class BBQ: blocking bounded queue 
 * This container class is thread-safe: 
 * if the queue is full, the thread calling insert() will block until
 *   an item has been removed from the queue
 * if the queue is empty, the thread calling remove() will block until
 *    an item has been inserted into the queue */

//header file for POSIX thread library 
#include <pthread.h>
#include <string>
#include <cstdlib>
using namespace std;
const int MAX=5;

class BBQ {
 private:
	//syncrhonziation variables
	pthread_mutex_t lock;
	pthread_cond_t itemAdded;
	pthread_cond_t itemRemoved;

	//state variables
	string items[MAX];
	int front;
	int nextEmpty;

public:
	BBQ();

	
	
	void insert (string item);

	string remove();

}; 
