#ifndef _MYEPOLL_H_
#define _MYEPOLL_H_
#include<sys/epoll.h>

#define EPOLLSIZE 1024
#define FDSIZE 1024

class myepoll{
    private:
        int epollfd;
        int listenfd;
        struct epoll_event events[EPOLLSIZE];
    public:
        myepoll(const char* host, int port);

        int mysocket();

        int mybind(const char* host, int port);

        int mylisten();

        void handle_events(int num);

        void handle_accept();

        void add_event(int fd, int state);

        void del_event(int fd, int state);

        void mod_event(int fd, int state);

        void do_read(int fd);

        void do_write(int fd);

        void do_epoll();
};
#endif
