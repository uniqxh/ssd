#include<stdio.h>
#include<assert.h>
#include<sys/select.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/time.h>

int main(){
	int kb = open("/dev/tty", O_RDONLY | O_NONBLOCK);
	assert(kb>0);
	char c;
	int ret, i;
	fd_set readfd;
	struct timeval timeout;
	while(1){
		timeout.tv_sec = 1;
		timeout.tv_usec= 0;
		FD_ZERO(&readfd);
		FD_SET(kb, &readfd);
		ret = select(kb + 1, &readfd, NULL, NULL, &timeout);
		if(ret == -1) perror("select error");
		else if(ret == 0) printf("time out");
		else if(FD_ISSET(kb, &readfd)){
			i = read(kb, &c, 1);
			if('\n' == c) continue;
			printf("the input is %c\n", c);
			if('q' == c) break;
		}
	}
	return 0;
}
