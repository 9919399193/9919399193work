clialia = echoclient.o echoinput.o readline.o my_err.o

client:$(clialia)
	cc -o client $(clialia)

echoclient.o:unp.h
echoinput.o:unp.h
readline.o:unp.h
my_err.o:unp.h

.PHONY:clean
clean:
	-rm client $(clialia)