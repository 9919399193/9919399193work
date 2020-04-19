#include "unp.h"

extern ssize_t Readline(int fd,void* vptr,size_t maxlen);

void str_cli(FILE* fp,int sockfd){
	char sendline[MAXLINE],recvline[MAXLINE];
	while(fgets(sendline,MAXLINE,fp)!=NULL){
		Write(sockfd,sendline,strlen(sendline));
		if(Readline(sockfd,recvline,MAXLINE)==0)
			err_quit("str_cli: server terminated prematurely");
		fputs(recvline,stdout);
	}
}