#include <stdio.h>

int asserterrors = 0;

#define asserttrue(expression) do \
{ \
	if(!(expression)) \
	{ \
		fprintf(stdout, "Assertion error\n"); \
		asserterrors++; \
	} \
	else \
        { \
		fprintf(stdout, "Pass\n"); \
	} \
}while(0) 
