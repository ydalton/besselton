LIBS=-lm
CFLAGS=-Wall -Wpedantic -DDEBUG

besselton: besselton.o
	cc besselton.o $(LIBS) $(CFLAGS) -o besselton
clean:
	rm -f besselton besselton.o
