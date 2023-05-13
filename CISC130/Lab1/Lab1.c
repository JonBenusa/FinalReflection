#include <stdio.h>
#include <string.h>

int copy_stuff(int x, int y, char *s);


int main(int argc, char *argv[]){

	copy_stuff(5, 10, argv[1]);
	return 0;
}


int copy_stuff(int x, int y, char *s){
	int z; // this is line 15
	char abc[60];
	z = x+y;
	strcpy(abc,s);
	printf("z is at %p \n", &z);
	printf("z is %d \n", z);
	return z;
}
