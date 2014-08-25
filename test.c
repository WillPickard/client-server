#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){

	char c1,c2,c3,c4;
	c1='a';
	c2='b';
	c3='c'; 
	c4='d';
	printf("First: %c, %c, %c, %c,\n",c1,c2,c3,c4);

  c1-=32;
  c2-=32;
  c3-=32;
  c4-=32;

	printf("second: %c, %c, %c, %c,\n",c1,c2,c3,c4);

  
  char a='a';
	char capA='A';
	printf("%c:%d %c:%d\n",a,a,capA,capA);
  char b='b';
	char capB='D';
	printf("%c:%d %c:%d\n",b,b,capB,capB);
	
  char alph[26];
	char cap[26];
	int i=0;
	while( i<26){
    alph[i]=i+97;
    cap[i]=i+65;
    printf(" %c: %d ",alph[i],alph[i]);
    printf(" %c: %d \n",cap[i],cap[i]);
		i++;
	}

	char test[12];
	i=0;
	while(i<12){
		test[i]=i+90;
		printf("\n");
    printf("%c: %d",test[i],test[i]);
		i++;
	}
	fflush(0);

	
return 0;
}
