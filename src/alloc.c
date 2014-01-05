#include <stdio.h>

#define ALLOCSIZE 1000

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *alloc(int n){
	if (allocbuf + ALLOCSIZE > allocp + n){
		allocp += n;
		return allocp - n;
	}
}

void afree(int *p){
	if (p >= allocbuf && p < allocbuf + ALLOCSIZE){
		allocp = p;
	}
}


void main(){
	char *hello = alloc(6);
	hello = "hello";

	char *world = alloc(6);
	world = "world";

	char *end = alloc(12);
	end = "hello world!";



	printf("%s\n", hello);
}
