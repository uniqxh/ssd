#include<stdio.h>
#include<unistd.h>

int main(){
    printf("using _exit.\n");
    printf("this is a content in buffer");
    _exit(0);
}
