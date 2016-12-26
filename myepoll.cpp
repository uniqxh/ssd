#include "myepoll.h"
#include<sys/socket.h>
#include<string.h>
#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

myepoll::myepoll(const char* host, int port){
    listenfd = mysocket();
    mybind(host, port);
    mylisten();
    printf("listenfd: %d\n", listenfd);
    do_epoll();
}

int myepoll::mysocket(){
    printf("create socket.\n");
    return socket(AF_INET, SOCK_STREAM, 0);
}

int myepoll::mybind(const char* host, int port){
    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, host, &addr.sin_addr);
    printf("bind socket.\n");
    return bind(listenfd, (struct sockaddr*)&addr, sizeof(addr));
}

int myepoll::mylisten(){
    return listen(listenfd, 10);
}

void myepoll::do_epoll(){
    epollfd = epoll_create(10);
    add_event(listenfd, EPOLLIN);
    int ret;
    while(1){
        ret = epoll_wait(epollfd, events, EPOLLSIZE, 0);
        handle_events(ret);
    }
    close(epollfd);
}

void myepoll::handle_events(int num){
    int i, fd, ev;
    for(i = 0; i<num; ++i){
        fd = events[i].data.fd;
        ev = events[i].events;
        if(fd == listenfd && ev & EPOLLIN)
            handle_accept();
        else if(ev & EPOLLIN)
            do_read(fd);
        else if(ev & EPOLLOUT)
            do_write(fd);
    }
}

void myepoll::handle_accept(){
    struct sockaddr_in addr;
    socklen_t len;
    int ret = accept(listenfd, (struct sockaddr*)&addr, &len);
    if(ret == -1){
        perror("accept error:");
    }else{
        printf("accept a new client[%d]: %s:%d\n", ret, inet_ntoa(addr.sin_addr), addr.sin_port);
        add_event(ret, EPOLLIN);
    }
}

void myepoll::add_event(int fd, int state){
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = state;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
}

void myepoll::del_event(int fd, int state){
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = state;
    epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &ev);
}

void myepoll::mod_event(int fd, int state){
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = state;
    epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &ev);
}

void myepoll::do_read(int fd){
    char buf[1024] = {0};
    int ret = read(fd, buf, 1024);
    if(ret == -1){
        perror("read error");
        close(fd);
        del_event(fd, EPOLLIN);
    }else if(ret == 0){
        printf("client[%d] closed.\n", fd);
        close(fd);
        del_event(fd, EPOLLIN);
    }else{
        printf("from: %s\n", buf);
        mod_event(fd, EPOLLOUT);
    }
}

void myepoll::do_write(int fd){
    char buf[1024] = "accepted";
    int ret = write(fd, buf, strlen(buf));
    if(ret == -1){
        perror("write error:");
        close(fd);
        del_event(fd, EPOLLOUT);
    }else{
        mod_event(fd, EPOLLIN);
    }
}
