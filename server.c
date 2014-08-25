#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <unistd.h>
#define MY_PORT 5187
#define MAXSIZE 256
int main(void){//int argc, char * argv[]){
	int status,socketId;
	struct sockaddr_in myAddress;//my packet
	struct sockaddr_in  connectionAddress;
  char buf[MAXSIZE];
  int yes=1;


	if((socketId=socket(AF_INET,SOCK_STREAM,0))==-1){
		perror("socket");
		exit(1);
	}
  //we have a socket, now we have to bind it to a file
	
  myAddress.sin_family=AF_INET;
	myAddress.sin_port=htons(MY_PORT);
	myAddress.sin_addr.s_addr=htonl(INADDR_ANY);//fill in the ip for me
  memset(myAddress.sin_zero, '\0', sizeof myAddress.sin_zero);//set contents of hints to all 0's
  
	if(setsockopt(socketId, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int))==-1){
		perror("setsockopt");
		exit(1);
	}
printf("socket options created, operating on address: %s",myAddress.sin_addr.s_addr);	
	if(bind(socketId, (struct sockaddr*)&myAddress, sizeof myAddress)==-1){
		perror("bind");
		exit(1);
	}

	if(listen(socketId,5)){
		perror("listen");
		exit(1);
	}

	printf("listening...\n");

	while(1){
		int socketConnection, len, done, bytesReceived;
		printf("Waiting for connection...\n");
    socklen_t connectionlen=sizeof(&connectionAddress);
		
		if((socketConnection=accept(socketId, (struct sockaddr *)&connectionAddress, &len))==-1){
		  perror("acccept");
			continue;
		}

		printf("Received connection from: %s",inet_ntoa(connectionAddress.sin_addr));
		done=0;
		do{//read message, write it to buffer, caps, and send back	
			bytesReceived=recv(socketConnection, buf, MAXSIZE-1, 0);//bytesReceived now holds number of bytes contained in the socket that the client wrote to
			if(bytesReceived<=0){//either there was nothing to read or something bad happened
				if(bytesReceived<0){perror("recv on server"); exit(1);}
				else done=1;
			}

			if(!done){
			  
				printf("I think the client just said: %s\n", buf);
				
				//below handles toCaps
				int i=0;
				while(buf[i]){
					char c = buf[i];
					if((int)c > 96){
						buf[i]=(c-32);
					}
					i++;
				}

				if(send(socketConnection, buf, bytesReceived, 0)<0){
					perror("send");
					exit(1);
				}
			}
		}while(!done);
		//close(socketConnection);
	}//end accept while
return 0;
}
