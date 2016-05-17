#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "bbq.h"
#include <fstream>
/*
Program to test HTML downloader
author: Liam Paris
*/
using namespace std;
BBQ queue;
int result; 
void * consumer_routine (void * arg)
{
//obtains the url and runs the system command on it before exiting
	while(1)
	{		
		const int COMMAND_LINE_LEN=256;
		char commandLine[COMMAND_LINE_LEN];
		string value = queue.remove();
		cout<< "Obtained website: "<<value<<" downloading now"<<endl; 
		int valSize = value.size();
		char url[valSize];
		for(int i =0;i<valSize;i++)
		{
			url[i] = value[i];
		}
		url[valSize] ='\0';
		sprintf (commandLine,"curl %s",url); 
		system (commandLine);
	}
}

int main(int argc, char *argv[])
{
	//puts contents of file into queue
	int numThreads = atoi(argv[1]);//turns into integer
	string fileName=argv[2];
	cout<< "filename "<< fileName<<endl;
	pthread_t consumerThreads[numThreads];
	ifstream file(fileName.c_str());
   string content;
	int i = 0;
	while(file >> content) 
 	{
		cout<< content<<endl;
		queue.insert(content);
		i++;
    }
	
	
	// create 10 threads, each remove an item from the queue 
	for (int i=0;i<numThreads;i++)
	{
		cout<< "creating thread "<<i<<endl;
		pthread_create (&consumerThreads[i],NULL,
			consumer_routine, NULL);
	}

	//main thread wait for all threads to finish 
	for (int i=0;i<numThreads;i++)
	{
		pthread_join (consumerThreads[i], (void **)&result);
		printf ("%d-th consumer thread return %d\n",i, result);
	}
}
