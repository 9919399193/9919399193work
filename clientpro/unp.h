#ifndef __unp_h
#define __unp_h

#include <sys/types.h> //basic system data types, time_t 
#include <sys/socket.h> //basic socket definitions
#include <sys/time.h>
#include <time.h>
#include <netinet/in.h> //sockaddr_in(),including ip addr/tcp udp port/addr family
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/un.h>

#define LISTENQ 1024
#define MAXLINE 4096
#define BUFFSIZE 8192

#define SA struct sockaddr

int Socket(int family,int type,int protocol);
int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
int Listen(int sockfd, int backlog);
int Write(int fd,void *buffer,int length);
int Read(int fd,void *buffer,int length);
int Close(int fd);
int Connect(int sockfd,const struct sockaddr* addr,socklen_t addrlen);

void err_ret(const char *fmt, ...);
void err_sys(const char *fmt, ...);
void err_exit(int error, const char *fmt, ...);
void err_dump(const char *fmt, ...);
void err_msg(const char *fmt, ...);
void err_quit(const char *fmt, ...);
static void err_doit(int errnoflag, int error, const char *fmt, va_list ap);

#endif

#ifdef HAVE_SYS_SELECT_H
#include <sys/select.h>
#endif

#ifdef HAVE_SYS_SYSCTL_H
#include <sys/sysctl.h>
#endif

#ifdef HAVE_POLL_H
#include <poll.h>
#endif

#ifdef HAVE_SYS_EVENT_H
#include <sys/event.h>
#endif

#ifdef HAVE_STRINGS_H
#include <strings.h>
#endif

#ifdef HAVE_SYS_IOCTL_H
#include  <sys/ioctl.h>
#endif

#ifdef HAVE_SYS_FILEIO_H
#include <sys/fileio.h>
#endif

#ifdef HAVE_SYS_SOCKIO_H
#include <sys/sockio.h>
#endif

#ifdef HAVE_PTHREAD_H
#include <pthread.h>
#endif

#ifdef HAVE_NET_IF_DL_H
#include <net/if_dl.h>
#endif

#ifdef HAVE_NETINET_SCTP_H
#include <netinet/sctp.h>
#endif