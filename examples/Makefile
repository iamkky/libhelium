
CC = gcc
CFLAGS+=-Wall
CFLAGS+=-I..
CFLAGS+=-L$(LIBABD) -I$(LIBABD)

all: form example1

form: form.o
	$(CC) $(CFLAGS) form.o -o form -labd ../libhelium.a

example1: example1.o
	$(CC) $(CFLAGS) example1.o -o example1 -labd ../libhelium.a

clean:
	rm -f *.o form example1



