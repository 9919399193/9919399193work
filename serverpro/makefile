seralia = echoserver.o echostr.o my_err.o

server:$(seralia)
	cc -o server $(seralia)

my_err.o:my_err.c
echoserver.o:unp.h
echostr.o:unp.h

.PHONY:clean
clean:
	-rm server $(seralia)