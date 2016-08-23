#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <libgen.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>


#define BUF_SIZE 4096

const char USAGE[]="mywget domain path [port]\n"
  "\n"
  "connect to the web server at domain and port, if provided, and request\n"
  "the file at path. If the file exist, save the file based on the\n"
  "filename of value in the path\n"
  "\n"
  "If domain is not reachable, report error\n";

//USEFUL for making requests
const char GET[]="GET ";             //start of GET request
const char END_GET[]=" HTTP/1.0\n\n\r\r"; //end of GET request, between is the path

//PASS CODE
const char ACCEPT_200[]="HTTP/1.1 200 OK\n";

//ERROR CODES
const char ERROR_300[]="HTTP/1.1 300 Multiple Choices\n";
const char ERROR_301[]="HTTP/1.1 301 Moved Permanently\n";
const char ERROR_400[]="HTTP/1.1 400 Bad Request\n";
const char ERROR_403[]="HTTP/1.1 403 Forbidden\n";
const char ERROR_404[]="HTTP/1.1 404 Not Found\n";
const char ERROR_500[]="HTTP/1.1 500 Internal Server Error\n";

int main(int argc, char *argv[]){

  short port=80;                 //the port we are connecting on

  struct addrinfo *result;       //to store results
  struct addrinfo hints;         //to indicate information we want

  struct sockaddr_in *saddr_in;  //socket interent address

  int s,n;                       //for error checking

  int sock;                      //socket file descriptor
  int fd;                        //output file


  char response[BUF_SIZE];           //read in BUF_SIZE byte chunks

  if( argc < 3){
    fprintf(stderr, "ERROR: Require domain and path\n");
    fprintf(stderr, "%s", USAGE);
    exit(1);
  }

  //retrieve the port if provided
  if (argc > 3){
    if((port = atoi(argv[3])) == 0){
      fprintf(stderr, "ERROR: invlaid port number\n");
      fprintf(stderr, "%s", USAGE);
      exit(1);
    }
  }


  //TODO Complete the lab
  //
  // Outline:
  //    - lookup domain to get socket address
  //    - add the port to the address
  //    - open and connect the socket
  //    - send the get request for the path
  //    - read the response, check the code (use strcmp on just the numeric part)
  //    - write the response from server to the basename of the file 
  //    - cleanup by closing files

  
 
  //setup our hints
  memset(&hints,0,sizeof(struct addrinfo));  //zero out hints
  hints.ai_family = AF_INET; //we only want IPv4 addresses

  //Convert the hostname to an address
  if( (s = getaddrinfo(argv[1], NULL, &hints, &result)) != 0){
    fprintf(stderr, "ERROR: getaddrinfo: %s: %s\n",gai_strerror(s), argv[1]);
    exit(1);
  }
 
  //convert generic socket address to inet socket address
  saddr_in = (struct sockaddr_in *) result->ai_addr;

  //set the port in network byte order
  saddr_in->sin_port = htons(port);

  //open a socket
  if( (sock = socket(AF_INET, SOCK_STREAM, 0))  < 0){
    perror("socket");
    exit(1);
  }
 
  //connect to the server
  if(connect(sock, (struct sockaddr *) saddr_in, sizeof(*saddr_in)) < 0){
    perror("connect");
    exit(1);
  }
 
    if(port == 80){
      char request[1024];
      int i;
      for(i = 0; i < 4; i++)
	request[i] = GET[i];

      for(i = 0; i < strlen(argv[2]); i++)
	request[i + 4] = argv[2][i];

      for(i = strlen(argv[2]); i < strlen(argv[2]) + 14; i++)
	request[i + 4] = END_GET[i - strlen(argv[2])];

 
      //send the request
      
      if(write(sock,request,strlen(request)) < 0){
	perror("send");
      }
 
      //read the response until EOF
      while( (n = read(sock, response, 4096)) > 0){

	//check the code
	if(! strncmp(response+9,"300",3)){
	  fprintf(stderr, "%s", ERROR_300);
	  exit(1);
	}
	else if(! strncmp(response+9,"301",3)){
	  fprintf(stderr, "%s", ERROR_301);
	  exit(1);
	}
	else if(! strncmp(response+9,"400",3)){
	  fprintf(stderr, "%s", ERROR_400);
	  exit(1);
	}
	else if(! strncmp(response+9,"403",3)){
	  fprintf(stderr, "%s", ERROR_403);
	  exit(1);
	}
	else if(! strncmp(response+9,"404",3)){
	  fprintf(stderr, "%s", ERROR_404);
	  exit(1);
	}
	else if(! strncmp(response+9,"500",3)){
	  fprintf(stderr, "%s", ERROR_500);
	  exit(1);
	}
	else if(! strncmp(response+9,"200",3)){
	  fd = open(basename(argv[2]), O_CREAT | O_WRONLY, 0666);  
	  while(n > 0){	 
	    //write response to stdout
	    if(write(fd, response, n) < 0){
	      perror("write");
	      exit(1);
	    }
	    n = read(sock, response, 4096);
	  }
	    fprintf(stderr, "%s", ACCEPT_200);
	  
	}


   
      }

      if (n<0){
	perror("read");
      }



      //close the socket
      close(sock);
    }
    else{
      while( (n = read(sock, response, 4096)) > 0){
	fd = open(basename(argv[2]), O_CREAT | O_TRUNC | O_WRONLY, 0666);  
	if(write(fd, response, n) < 0){
	  perror("write");
	  exit(1);
	}
      }
      
    }
    return 0; //success
}
