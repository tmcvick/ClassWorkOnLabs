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

char* getContentType(char* filename);
char* concat(char* s1, char* s2);

short port;
char* directory;

int main(int argc, char* argv[]){

  port = 8080;
  directory = "./";
  int i;
  for(i =1; i < argc; i++)
    {
      if(argv[i][0] == '-' && argv[i][1] == 'p')
	port = atoi(argv[++i]);
      else
	directory = argv[i];
    }

  if(directory[strlen(directory) - 1] != '/')
    {
      directory = strcat(directory, "/");
    }

  struct sockaddr_in saddr;
  struct sockaddr_in caddr;

  int ssock;
  int csock;

  if((ssock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
      perror("socket");
      exit(1);
    }

    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    saddr.sin_port = htons(port);

    if(bind(ssock, (struct sockaddr *)&saddr, sizeof(saddr)) < 0)
      {
	perror("bind");
	exit(1);
      }

    if(listen(ssock, 5) < 0)
      {
	perror("listen");
	exit(1);
      }

    while(1)
      {

	socklen_t socklen = sizeof(caddr);

	if((csock = accept(ssock, (struct sockaddr *) &caddr,
			   &socklen)) < 0)
	  {
	    perror("accept");
	    exit(1);
	  }

	char* buf = malloc(1024);
	char* tmp = malloc(1024);
	char* tmp2 = malloc(1024);
	int resSize;
	int request = 1;
	char* res = malloc(1024);
	char* code = malloc(3);
	char* file;
	int len = 0;
	char* length = malloc(5);
	char* http = malloc(1024);
	char c;
	int error = 0;
	int flag = 0;
	char* date = malloc(1000);
	char* lmdate = malloc(1000);
	struct stat status;
	struct tm tim;
	time_t currTime;

	if((resSize = recv(csock, buf, 1024, 0)) < 0)
	  {
	    perror("recv");
	    exit(1);
	  }

	strcat(tmp, buf);
	strcat(res, "HTTP/1.1 ");

	//405 error
	if(strstr(tmp, "GET") == NULL ||
	   strcmp(tmp, strstr(tmp, "GET")) != 0)
	  {
	    if(strstr(tmp, "HEAD") == NULL ||
	       strcmp(tmp, strstr(tmp, "HEAD")) != 0)
	      {
		strcat(res, "405 Error : Unsupported request\r\nAllow: HEAD, GET\r\n");
		strcpy(code, "405");
		error = 1;
	      }
	    else
	      request = 0;
	  }


	//400 Error
	else if(strstr(tmp, "HTTP/1.1") == NULL) 
	  {
	    strcat(res, "400 Bad Request\r\n");
	    strcpy(code, "400");
	    error = 1;
	    flag = 1;
	  }

	if(flag == 0) 
	  {
	    strcpy(tmp2, tmp);
	    strtok(tmp2, " ");
	    file = strtok(NULL, " ");
      
	    // 403 error
	    if(strstr(file, "..") != NULL) 
	      {
		strcat(res, "403 Forbidden\r\n");
		strcpy(code, "403");
		error = 1;
	      }
	  }
	FILE* path;
	//file errors
	if(error == 0) 
	  {
	    path = fopen(concat(directory, file), "r");
	    if(path == NULL) 
	      {
		//404 error
		if(errno == 2) 
		  {
		    strcat(res, "404 Error: File not found\r\n");
		    strcpy(code, "404");
		    error = 1;
		  }
		//403 error
		else if(errno == 13) 
		  {
		    strcat(res, "403 Forbidden\r\n");
		    strcpy(code, "403");
		    error = 1;
		  }
	      }
	    //OK
	    else 
	      {
		strcat(res, "200 OK\r\n");
		strcpy(code, "200");
	      }
	  }
	strcat(res, "Connection: close\r\n");
	strcat(res, "Server: webserver/1.0\r\n");

	//Date
	strcat(res, "Date: ");
	time(&currTime);
	tim = *localtime(&currTime);
	strftime(date, 1000, "%a, %d %b %Y %H:%M:%S", &tim);
	strcat(res, date);
	strcat(res, "\r\n");

	strftime(date, 1000, "%a %b %Y %H:%M", &tim);

	if(error == 0)
	  {
	    strcat(res, "Last-Modified: ");
	    stat(concat(directory, file), &status);
	    tim = *localtime(&(status.st_mtime));
	    strftime(lmdate, 1000, "%a, %d %b %Y %H:%M:%S", &tim);
	    strcat(res, lmdate);
	    strcat(res, "\r\n");

	    strcat(res, "Content -Type: ");
	    strcat(res, getContentType(file));
	    if(request == 1)
	      {
		while((c = fgetc(path)) != EOF)
		  {
		    http[len] = c;
		    len++;
		  }
		http[len] = '\0';
		sprintf(length, "%d", len);

		strcat(res, "Content -Length: ");
		strcat(res, length);
		strcat(res, "\r\n\r\n");
		strcat(res, http);
	      }
	    else
	      strcat(res, "\r\n");
	  }
	else
	  strcat(res, "\r\n");

	if(flag == 1)
	  printf("%s\t%s\n", date, code);
	else
	  printf("%s\t%s\t%s\t%s\n", tmp2, file+1, date, code);

	ssize_t num = send(csock, res, strlen(res), 0);
	if(num < 0)
	  {
	    perror("send");
	    exit(1);
	  }	
	else if(num != strlen(res))
	  {
	    perror("send");
	    exit(1);
	  }
	close(csock);
      }
    
    
  return 0;
}

char * getContentType(char* file_name)
{
  char * type = malloc(1024);

  if(strcmp(strrchr(file_name, '.'), ".html") == 0 ||
     strcmp(strrchr(file_name, '.'), ".htm") == 0)
    {
      strcat(type, "text/html\r\n");
    }
  else if(strcmp(strrchr(file_name, '.'), ".css") == 0)
    {
      strcat(type, "text/css\r\n");
    }
  else if(strcmp(strrchr(file_name, '.'), ".js") == 0)
    {
      strcat(type, "application/javascript\r\n");
    }
  else if(strcmp(strrchr(file_name, '.'), ".txt") == 0)
    {
      strcat(type, "text/plain\r\n");
    }
  else if(strcmp(strrchr(file_name, '.'), ".jpg") == 0)
    {
      strcat(type, "image/jpeg\r\n");
    }
  else if(strcmp(strrchr(file_name, '.'), ".pdf") == 0) {
    strcat(type, "application/pdf\r\n");
  }
  else
    {
      strcat(type, "application/octet-stream\r\n");
    }

  return type;
}



char * concat(char *s1, char *s2)
{
  char *result = malloc(strlen(s1)+strlen(s2)+1);
  strcpy(result, s1);
  strcat(result, s2);
  return result;

}
