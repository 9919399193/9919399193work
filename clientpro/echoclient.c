#include "unp.h"

extern void str_cli(FILE* fp,int sockfd);

int main(int argc,char** argv){
	int sockfd;
	struct sockaddr_in servaddr;
	if(argc!=2)
		err_quit("usage: tcpcli <IPaddress>");
	sockfd=Socket(AF_INET,SOCK_STREAM,0);
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(9877);
	inet_pton(AF_INET,argv[1],&servaddr.sin_addr);
	Connect(sockfd,(SA*)&servaddr,sizeof(servaddr));
	str_cli(stdin,sockfd);
	exit(0);
}