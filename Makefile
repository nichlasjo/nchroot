CC=cc
CFLAGS=-W -Wall -static -O2 -ansi -std=c11

nchroot: nchroot.o
nchroot.o: nchroot.c

static: 
	cc $(CFLAGS) -o nchroot nchroot.c
clean:
	$(RM) nchroot nchroot.o
run:
	./nchroot / top -b -n 1
