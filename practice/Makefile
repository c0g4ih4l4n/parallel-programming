CC=gcc
CFlags=-I.
DEPS = hellomake.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hellomake: hello.o hellofunc.o 
	$(CC) -o hellomake hello.c hellofunc.c
