#include<stdio.h>
#include<pthread.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>

int ticket_num = 20;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* fun(void* arg){
    for(int i = 0; i < 20; ++i){
        pthread_mutex_lock(&mutex);
        if(ticket_num > 0){
            printf("fun1 sell %d ticket.\n", 20 - ticket_num + 1);
            ticket_num --;
        }
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    return 0;
}

void* fun2(void* arg){
    int ret = 0;
    for(int i = 0; i < 10; ++i){
        ret = pthread_mutex_trylock(&mutex);
        if(ret == EBUSY){
            printf("fun2: locked by fun1.\n");
        }else if(ret == 0){
            if(ticket_num > 0){
                printf("fun2 sell %d ticket\n", 20 - ticket_num + 1);
                ticket_num--;
            }
            pthread_mutex_unlock(&mutex);
        }
        sleep(1);
    }
    return 0;
}

int main(){
    pthread_t pid[2];
    int ret = pthread_create(&pid[0], NULL, &fun, NULL);
    if(ret){
        perror("pthread create error:");
        return ret;
    }
    ret = pthread_create(&pid[1], NULL, &fun2, NULL);
    if(ret){
        perror("pthread create error:");
        return ret;
    }
    sleep(30);
    void* v;
    for(int i = 0; i < 2; ++i){
        pthread_join(pid[i], &v);
        printf("thread return code: %ld\n", (long)v);
    }
    return 0;
}
