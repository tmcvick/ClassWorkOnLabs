#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <pthread.h>

#define BUF_SIZE 4096
int i = 0;

void * client_handler(void * args){
  //TODO: Complete the client handler
  //
  // HINT: Consider what arguments need to be passed to client handler
  //       to print the right info.
  //
  // Output print statements:
  //
  //   printf("Received From: %s:%d (%d): %s", inet_ntoa(client_saddr_in.sin_addr),
  //           ntohs(client_saddr_in.sin_port), client_sock, response);
  //
  //    printf("Received From: %s:%d (%d): %s", inet_ntoa(client_saddr_in.sin_addr),
  //            ntohs(client_saddr_in.sin_port), client_sock, response);
  
  socklen_t saddr_len = sizeof(struct sockaddr_in); //length of address
  struct sockaddr_in client_saddr_in;  
  int * client_sock = (int *) args;
  int n;
  char response[BUF_SIZE];           //what to send to the client
  memset(response, 0, BUF_SIZE);
 
  getpeername(*client_sock, (struct sockaddr *) &client_saddr_in, &saddr_len);
  
  
  //read from client and echo back
  while( (n = read(*client_sock, response, BUF_SIZE)) > 0){
    
    

      //client sent a message
      
      //null response for safety
      response[n] = '\0';
      
      //write message back to client
      write(*client_sock, response, n);
      
      //LOG
      printf("Received From: %s:%d (%d): %s", inet_ntoa(client_saddr_in.sin_addr), 
	     ntohs(client_saddr_in.sin_port), *client_sock, response);
      
  }
  
  if(n == 0){
    //client close socket
    
    
    
    //LOG
    printf("Client Closed: %s:%d (%d)\n", inet_ntoa(client_saddr_in.sin_addr), 
	   ntohs(client_saddr_in.sin_port), *client_sock);
    
    //close client sockt
    close(*client_sock);
    
  }
  
}


int main(){
  //TODO: Complete the main function
  //
  // HINT: When you start a thread, you should detach it so that you
  //       do not have to join it later. Use: pthread_detach()
  char hostname[]="127.0.0.1";   //localhost ip address to bind to
  short port=1845;               //the port we are to bind to


  struct sockaddr_in saddr_in;  //socket interent address of server
  struct sockaddr_in client_saddr_in;
  socklen_t saddr_len = sizeof(struct sockaddr_in); //length of address

  int server_sock;         //socket file descriptor
  
  

  pthread_t thread[5];

//set up the address information
  saddr_in.sin_family = AF_INET;
  inet_aton(hostname, &saddr_in.sin_addr);
  saddr_in.sin_port = htons(port);

//open a socket
  if( (server_sock = socket(AF_INET, SOCK_STREAM, 0))  < 0){
    perror("socket");
    exit(1);
  }
  
  //bind the socket
  if(bind(server_sock, (struct sockaddr *) &saddr_in, saddr_len) < 0){
    perror("bind");
    exit(1);
  }

//ready to listen, queue up to 5 pending connectinos
  if(listen(server_sock, 5)  < 0){
    perror("listen");
    exit(1);
  }

  
  saddr_len = sizeof(struct sockaddr_in); //length of address

  printf("server sock listening: (%d)\n",server_sock);

  while(1){
    int* client_sock = malloc(sizeof(int));
    *client_sock = accept(server_sock, (struct sockaddr *) &client_saddr_in, &saddr_len);
   
    pthread_create(&thread[i], NULL, client_handler, client_sock);
    pthread_detach(thread[i]);
    i++;

  }
  close(server_sock);
  return 0; //success
}
