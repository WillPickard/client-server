#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netdb.h>
#include <netinet/in.h>


#define CONNECT_PORT 5187 
#define MAXBUFSIZE 256
int main(int argc, char *argv[]){
  int sid, len, bytesReceived;	
	struct sockaddr_in serverAddress;
	struct hostent *hostEntity;
	char buf[MAXBUFSIZE];

  if(argc<2){printf("Second arg is IP to connect to. Closing."); exit(0);}

  if((hostEntity=gethostbyname(argv[1]))==NULL){
		perror("gethostbyname");
		exit(1);
	}

	if((sid=socket(AF_INET, SOCK_STREAM, 0))==-1){
		perror("socket");
		exit(1);
	}

	printf("trying to connect...\n");

	serverAddress.sin_family=AF_INET;
	serverAddress.sin_port=htons(CONNECT_PORT);
	serverAddress.sin_addr = *((struct in_addr *)hostEntity->h_addr);//get the first address in the host address list
	memset(&serverAddress.sin_zero, '\0', sizeof serverAddress.sin_zero);
	
	if(connect(sid, (struct sockaddr *)&serverAddress, sizeof(serverAddress))==-1){
		perror("connect");
		exit(1);
	}

	printf("connected...\n");

  while(printf("> "), read(0,buf, MAXBUFSIZE)){
    if(send(sid, buf, strlen(buf), 0)==-1){
			perror("Send");
			exit(1);
		}
		
		if((bytesReceived=recv(sid,buf, MAXBUFSIZE, 0))>0){
			buf[t]='\0';
			printf("The server thinks you said: %s",buf);
		}
		else{
      if(bytesReceivedt<0){perror("recv"); exit(1);}
			else{
				printf("Server connection closed\n");
				exit(1);
			}
		}
	}
close(sid);
return 0;
}
