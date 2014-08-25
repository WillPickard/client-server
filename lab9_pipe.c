#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
#include<stdlib.h>
#include <string.h>

int main(void){
  int  status, childFifo[2], parentFifo[2];
	ssize_t bw, bread;
	char buf[128],buf1[128];
	pid_t child_pid,wait_pid;
	if(pipe(childFifo)==-1){perror("error on pipe"); exit(EXIT_FAILURE);}
	if(pipe(parentFifo)==-1){perror("error on pipe"); exit(EXIT_FAILURE);}
	
	switch(child_pid=fork()){
		case (-1):
			perror("error on fork");
			exit(EXIT_FAILURE);
		case 0:
			//child process, child will read from childFifo and write to parentFifo	
//			printf("%d\n",strlen(buf));
			bw=read(childFifo[0],buf,sizeof(buf)-1);
			printf("Did you say? ...  %s?\n",buf);
			int i=0;
			while(buf[i]){
        char c=buf[i];
				if((int)c > 96 ){
				  buf[i]=(c-32);
			}
				i++;
			}
			write(parentFifo[1],buf,bw);

			break;
		default:
			//parent
      printf("Enter a message>\n");
			bread=read(0, buf, sizeof(buf));
      write(childFifo[1],buf,bread);
	    do{
				wait_pid=waitpid(child_pid, &status, (WUNTRACED, WCONTINUED));
				if(wait_pid<0){perror("waitpid");exit(EXIT_FAILURE);}
				else if(wait_pid==0){continue;}
				else if (WIFEXITED(status)){
				 read(parentFifo[0], buf, sizeof(buf));
				 printf("Yes, I said: ... %s\n", buf);
			  }
			}while(!WIFEXITED(status) && !WIFSIGNALED(status));
	}//end switch
  return 0;
  }
