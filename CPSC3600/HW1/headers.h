/**
 *Author: Tim McVicker
 *Date: 30JAN2016
 *This file includes all libraries and header files required to run the 
 *valueServer and valueGuesser programs.  It also contains the function 
 *prototypes as well as the Node structure that is used in the programs.
 * functions included:
 *terminate_server()
 *terminate_client()
 *CatchAlarm()
 *timeval_subtract()
 */

#ifndef HEADERS_H
#define HEADERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <pthread.h>
#include <sys/select.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>

void terminate_server();
void terminate_client();
void CatchAlarm(int ignored);
int timeval_subtract (struct timeval *result, struct timeval *x, 
		      struct timeval *y);

struct Node
{
  struct sockaddr_in data;
  struct Node* next;
};


#endif
