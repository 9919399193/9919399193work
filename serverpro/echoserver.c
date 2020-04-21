#include "unp.h"

extern void str_echo(int sockfd);
extern void sig_chld(int signo);

int main(int argc,char** argv){
	int listenfd,connfd;
	pid_t childpid;
	socklen_t clilen;
	struct sockaddr_in cliaddr,servaddr;
	listenfd=Socket(AF_INET,SOCK_STREAM,0);
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(9877);
	Bind(listenfd,(SA* )&servaddr,sizeof(servaddr));
	Listen(listenfd,LISTENQ);
	
	signal(SIGCHLD,sig_chld);
	
	for(;;){
		clilen=sizeof(cliaddr);

		if((connfd=accept(listenfd,(SA* )&cliaddr,&clilen))<0){
			if(errno==EINTR){
				continue;
			}
			else
				err_sys("accept error");
		}
		
		if((childpid=fork())==0){
			Close(listenfd);
			printf("got it!\n");
			str_echo(connfd);
			exit(0);
		}
		Close(connfd);
	}
}