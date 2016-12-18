#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

int main(){
    pid_t pid, pr;
    pid = fork();
    if(pid < 0){
        perror("fork error:");
        exit(-1);
    }else if(pid == 0){
        printf("this is sub process\n");
        sleep(5);
        exit(33);
    }else{
        do{
            pr = waitpid(pid, NULL, WNOHANG);
            if(pr == 0){
                printf("No child exitd\n");
                sleep(1);
            }
        }while(pr == 0);
        if(pr == pid){
            printf("successfully get child %d\n", pr);
        }else printf("some error occured\n");
    }
    return 0;
}
