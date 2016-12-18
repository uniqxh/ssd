#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(){
    pid_t pid;
    int fd[2];
    pipe(fd);
    pid = fork();
    if(pid < 0){
        perror("fork error:");
        exit(1);
    }else if(pid == 0){
        close(fd[0]);
        write(fd[1], "hello", 5);
        exit(0);
    }else{
        close(fd[1]);
        char buf[100];
        int cnt = read(fd[0], buf, 100);
        printf("get data: %s\n", buf);
    }
    return 0;
}
