//Tim McVicker
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include <signal.h>
#include <time.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/stat.h>

short port;
char* filename = NULL;
char* URL;

int main(int argc, char* argv[]){

  port = 8080;
  int file = 0;
  struct hostent *host;
  struct in_addr saddr;
  char* server;
  char* path;
  char* hostIP;
  char* http = malloc(1024);
  FILE* output;

  if(argc == 2)
    URL = argv[1];
  if(argc < 2)
    {
      fprintf(stderr, "Usage: %s <URL> [-p <Port>] [-O <file_name>]\n", argv[0]);
      exit(1);
    } 

  int i;
  for(i = 2; (i < argc) && (argv[i][0] == '-'); i++)
    {
      if(argv[i][1] == 'p')
	port = atoi(argv[++i]);

      else if(argv[i][1] == 'o')
	{
	  filename = argv[++i];
	  file = 1;
	}
    }

  if(file > 0)
    output = fopen(filename, "w");

  server = (char*) malloc(sizeof(URL));
  path = (char*)malloc(sizeof(URL));

  server = strtok(URL, "/");
  server = strtok(NULL, "/");
  path = strtok(NULL, "\0");

  strcpy(http, "GET /");
  strcat(http, path);
  strcat(http, " HTTP/1.1\r\nHost: ");
  strcat(http, server);
  strcat(http, "\r\n\r\n");
  host = gethostbyname(server);
  bcopy(host->h_addr, (char*)&saddr, sizeof(saddr));

  hostIP = inet_ntoa(saddr);

  int csock;
  if((csock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
      perror("socket");
      exit(1);
    }
  
  struct sockaddr_in servAddr;
  memset(&servAddr, 0, sizeof(servAddr));
  servAddr.sin_family = AF_INET;

  if(( inet_pton(AF_INET, hostIP, &servAddr.sin_addr.s_addr)) <= 0)
    {
      perror("inet_pton");
      exit(1);
    }

  servAddr.sin_port = htons(port);

  if(connect(csock, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0)
    {
      perror("connect");
      exit(1);
    }

  size_t length = strlen(http);

  if((send(csock, http, length, 0)) != length)
    {
      perror("send");
      exit(1);
    }
  
  unsigned int bytes = 0;
  int toggle = 1;

  while(1)
    {
      char* buf = malloc(1024);
      ssize_t num;
      num = recv(csock, buf, 1023, 0);
      if(num < 0)
	{
	  perror("recv");
	  exit(1);
	}
      if(num == 0)
	break;

      bytes += num;
      buf[num] = '\0';

      if(toggle)
	{
	  if(file > 0)
	    fputs(strstr(buf, "\r\n\r\n")+4, output);
	  else
	    fputs(strstr(buf, "\r\n\r\n")+4, stdout);
	  toggle = 0;
	}
      else
	{
	  if(file > 0)
	    fputs(buf, output);
	  else
	    fputs(buf, stdout);
	}
    }

  fputc('\n', stdout);

  close(csock);

  return 0;
}
