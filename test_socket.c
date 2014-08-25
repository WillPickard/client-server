//@ file socket.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORT 8080
#define PORT1 4367

#define MAXDATASIZE 100
#define HUGEMAXDATASIZE 1028  //max number of bytes that can be read at one time

int main(int argc, const char* argv[]){

}
