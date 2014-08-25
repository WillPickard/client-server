#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define SOCK_PATH "my_echo_socket"

int main(void){
  int sid, sid2, t, len;
	struct sockaddr_un local,remote;//structure to define packets 
	char buf[256];//buffer

	if((sid=socket(AF_UNIX,SOCK_STREAM,0))==-1){
    perror("socket");
		exit(1);
	}
  printf("sid: %d\n",sid);
	local.sun_family=AF_UNIX;
	//local.sin_port=htons(4080);//convert 4080 from local byte order to network(big/small endian)
	strcpy(local.sun_path, SOCK_PATH);
	unlink(local.sun_path);
	
	//inet_pton(AF_INET, "10.0.0.1", &local.sin_addr);//inet_pton converts the string to a network address is signature and stores that in the struct located at address lcal.sin_addr
	len=strlen(local.sun_path)+sizeof(local.sun_family);
	if(bind(sid, (struct sockaddr *)&local, len)==-1){
		perror("bind");
		exit(1);
	};
  printf("listening..\n");
	if(listen(sid,2)==-1){
		perror("listen");
		exit(1);
	}

	for(;;){
		int done, bytesReceived;
		printf("Waiting for connection...");
		//lengthOf
		t=sizeof(local);
		if((sid2=accept(sid,(struct sockaddr*)&local, &t))==-1){
			perror("accept");
			exit(1);
		}

		printf("Connection made in sid: %d.\n",sid);
		printf("Sun_path: %s\n",local.sun_path);

		done=0;
		do{
			bytesReceived=recv(sid2, buf, sizeof(buf), 0);
			if(bytesReceived<=0){
				if(bytesReceived<0){perror("recv");}
				done=1;
			}
			if(!done){
			   printf("I think the client said: %s \n", buf);
         if(send(sid2,buf,bytesReceived,0)<0){
						perror("send");
						done=1;
						exit(1);
				 }
			}
		}while(!done);
		close(sid2);
	}
	return  0;
}
