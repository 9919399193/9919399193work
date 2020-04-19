#include <errno.h> /* for definition of errno */
#include <stdarg.h> /* ISO C variable aruments */
#include <stdlib.h>
#include "unp.h"

static void err_doit(int, int, const char *, va_list);

/*
 * Nonfatal error related to a system call.
 * Print a message and return.
 */
void
err_ret(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    err_doit(1, errno, fmt, ap);
    va_end(ap);
}


/*
 * Fatal error related to a system call.
 * Print a message and terminate.
 */
void
err_sys(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    err_doit(1, errno, fmt, ap);
    va_end(ap);
    exit(1);
}


/*
 * Fatal error unrelated to a system call.
 * Error code passed as explict parameter.
 * Print a message and terminate.
 */
void
err_exit(int error, const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    err_doit(1, error, fmt, ap);
    va_end(ap);
    exit(1);
}


/*
 * Fatal error related to a system call.
 * Print a message, dump core, and terminate.
 */
void
err_dump(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    err_doit(1, errno, fmt, ap);
    va_end(ap);
    abort(); /* dump core and terminate */
    exit(1); /* shouldn't get here */
}


/*
 * Nonfatal error unrelated to a system call.
 * Print a message and return.
 */
void
err_msg(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    err_doit(0, 0, fmt, ap);
    va_end(ap);
}


/*
 * Fatal error unrelated to a system call.
 * Print a message and terminate.
 */
void
err_quit(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    err_doit(0, 0, fmt, ap);
    va_end(ap);
    exit(1);
}


/*
 * Print a message and return to caller.
 * Caller specifies "errnoflag".
 */
static void
err_doit(int errnoflag, int error, const char *fmt, va_list ap)
{
    char buf[MAXLINE];
   vsnprintf(buf, MAXLINE, fmt, ap);
   if (errnoflag)
       snprintf(buf+strlen(buf), MAXLINE-strlen(buf), ": %s",
         strerror(error));
   strcat(buf, "\n");
   fflush(stdout); /* in case stdout and stderr are the same */
   fputs(buf, stderr);
   fflush(NULL); /* flushes all stdio output streams */
}

int Socket(int family,int type,int protocol){
    int n;
    if((n=socket(family,type,protocol))<0)
        err_sys("socket error");
    return n;
}

int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen){
    int n;
    if((n=bind(sockfd,addr,addrlen))<0)
        err_sys("bind error");
    return n;
}

int Listen(int sockfd, int backlog){ //backlog应该理解为阻塞队列的长度
    int n;
    if((n=listen(sockfd,backlog))<0)
        err_sys("listen error");
    return n;
}

int Write(int fd,void *buffer,int length)
{
    int bytes_left;
    int written_bytes;
    char *ptr;

    ptr=buffer;
    bytes_left=length;
    
    while(bytes_left>0)
    {
        written_bytes = write(fd,ptr,bytes_left);
        if(written_bytes<=0)
        {
            if(errno==EINTR)
                written_bytes=0;
            else{
                err_sys("write error");
                return -1;
            }
        }
        bytes_left-=written_bytes;
        ptr+=written_bytes;
    }
    return 0;
}

int Read(int fd,void *buffer,int length)
{
    int bytes_left;
    int bytes_read;
    char *ptr;
    
    bytes_left=length;
    while(bytes_left>0)
    {
        bytes_read=read(fd,ptr,bytes_read);
        if(bytes_read<0)
        {
            if(errno==EINTR)
                bytes_read=0;
            else{
                err_sys("read error");
                return -1;
            }
        }
        else if(bytes_read==0)
            break;
        bytes_left-=bytes_read;
        ptr+=bytes_read;
    }
    return(length-bytes_left);
}

int Close(int fd){
    int n;
    if((n=close(fd))<0)
        err_sys("close error");
    return n;
}