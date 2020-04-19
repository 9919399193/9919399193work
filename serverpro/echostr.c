#include "unp.h"

void str_echo(int sockfd){
	ssize_t n;
	char buf[MAXLINE];
	while(1){
		while((n=read(sockfd,buf,MAXLINE))>0){
			printf("%s",buf);
			Write(sockfd,buf,n);
		}
		if(n<0&&errno==EINTR);
		else if(n<0)
			err_sys("*str_echo: read error");
		else
			break;
	}
}