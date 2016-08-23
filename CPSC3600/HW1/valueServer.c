/**
 *Author: Tim McVicker
 *Date: 30JAN2016
 *This is the server program for HW 1.  The server picks a random number and 
 *listens for UDP datagrams from clients trying to guess the number, and 
 *returns a 0 if the guess is correct, 1 if too high, and 2 is too low.
 *Functions included are:
 *Main()
 *terminate_server()
 */

#include "headers.h"

//numMsgs is the number of msgs received, while numCorrect is number correct
int numMsgs, numCorrect;

int server_sock;         //socket file descriptor

//represents the clients that have contacted the server
struct Node *list;

int main(int argc, char* argv[])
{
  numMsgs = 0;
  numCorrect = 0;
  list = NULL;

  //value is the desired value. Seed random
  int value;
  time_t t;
  srand(time(&t));
 

  short port;  //port the server is listening on
  struct sockaddr_in saddr_in;  //socket interent address of server
 
  socklen_t saddr_len = sizeof(struct sockaddr_in); //length of address
 
  //check correct # arguments
  if(argc < 3 || argc > 5)
    {
      printf("Usage: %s -p <serverPort> -v <initialValue>\n", argv[0]);
      exit(1);
    }

  //read in arguments
  port = atoi(argv[2]);
  if(argc == 5)
    value = atoi(argv[4]);
  else
    value = rand() % 1000000000;

  //set up ctrl-C signal handler  
  signal(SIGINT, terminate_server);

  //set up the address information
  memset(&saddr_in, 0, sizeof(saddr_in));  
  saddr_in.sin_family = PF_INET;
  saddr_in.sin_addr.s_addr = htonl(INADDR_ANY);
  saddr_in.sin_port = htons(port);

  //open a socket
  if( (server_sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP))  < 0){
    perror("socket");
    exit(1);
  }

  //bind to socket
  if (bind(server_sock, (struct sockaddr *) &saddr_in, saddr_len) < 0){
    perror("bind");
    exit(1);
  }

  //for use in sendto() and recvfrom()
  socklen_t caddr_len; 
  struct sockaddr_in caddr_in;
  int msgsize, returnValue, clientsGuess;

  //loop and run indefinitely until ctrl-c
  while(1)
    {
      caddr_len = sizeof(caddr_in);

      //block until message incoming
      if ((msgsize = recvfrom(server_sock, &clientsGuess, sizeof(int), 0,
			      (struct sockaddr *) &caddr_in, &caddr_len)) < 0)
	{
	  perror("recvfrom");
	  exit(1);
	}
      
      //add client to list if not already there
      struct Node* iter = list;
      int c =0;
      while(iter != NULL)
	{
	  if(htonl(iter->data.sin_addr.s_addr) == 
	     htonl(caddr_in.sin_addr.s_addr))
	    c = 1;
	  iter = iter->next;
	}
      if(c == 0)
	{
	  struct Node *tmp = malloc(sizeof(struct Node));
	  tmp->data = caddr_in;
	  tmp->next = list;
	  list = tmp;
	}

      //increment numMasg
      numMsgs++;

      //set up return values and reactions
      //correct=0
      if(clientsGuess == value)
	{
	  printf("Answer Guessed\n");
	  numCorrect++;
	  returnValue = 0;

	  //choose new number
	  value = rand() % 1000000000;
	}

      //too high=1
      else if(clientsGuess > value)
	returnValue = 1;

      //too low=2
      else if(clientsGuess < value)
	returnValue = 2;

      //catch all
      else
	returnValue = -1;

      //reply to msg
      if(sendto(server_sock, &returnValue, sizeof(int), 0, 
		(struct sockaddr *) &caddr_in, sizeof(caddr_in)) < 0)
	{
	  perror("sendto");
	  exit(1);
	}

    }  
  return 0;
}

/**This function will terminate the server upon the SIGINT signal.
 *The function prints the termination message as required, first the number
 *of messages received, then the number of correct guesses, then the list
 *of clients.  The functions frees the malloc'd memory and closes the socket
 */
void terminate_server()
{
  printf("%i\t%i\t", numMsgs, numCorrect);
  if(!(list == NULL))
    {
      printf("%s", inet_ntoa(list->data.sin_addr));
      while(list->next != NULL)
	{
	  printf(",%s", inet_ntoa(list->next->data.sin_addr));
	  struct Node* tmp = list;
	  list = list->next;
	  free(tmp);
	}
      printf(",");
    }
  printf("\n");
  close(server_sock);
  exit(0);
}
