#include <stdio.h>
#include <stdlib.h>

int main ( int argc, char *argv)
{
	int length;
	if(argc != 3){
		printf("WRONG");
	}
	else
	{
		length = (int) malloc(sizeof(int));
		length = atoi(argv[1]);
		printf("%s", argv[0]);
		printf("%s", argv[1]);
	}
	return 0;
}
