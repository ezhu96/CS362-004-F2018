#include <stdio.h>

#define asserttrue(expression) do \
{ \
	if(!(expression)) \
	{ \
		fprintf(stderr, "Assertion error\n"); \
	} \
	else \
        { \
		fprintf(stdout, "Pass\n"); \
	} \
}while(0) 
