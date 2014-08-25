#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>


int main(void){
  // declare variables needed by parent or child
  // you'll need *two* arrays for fds
  
  // create two pipes and check for errors
  
  // fork off a child process
  
  // Set up the pipes so that the child can write to the parent on one pipe
  // and the parent can write to the child on the other pipe.
  
  // The parent should prompt the user for a message, and then write
  // the message to the child.  It should then wait for a response from
  // the child and respond "Yes, I said ..." and then echo that response 
  // to the screen.  
  // The parent should wait for the child to terminate.
  
  // The child should wait for a message from the parent.
  // It should echo the message to the screen (Did you say?: $whatever).
  // It should change the received message to all uppercase and 
  // then send it back to the parent.
  // The child should then exit.
  
  }
