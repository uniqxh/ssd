#include<stdio.h>
int main(){
#define to_literal(text) to_literal_(text)
#define to_literal_(text) #text
#ifndef __cplusplus
	printf("a c program\n");
#else
	printf("a C++ program\n__cplusplus expands to \""to_literal(__cplusplus)"\"\n");
#endif
	return 0;
}

