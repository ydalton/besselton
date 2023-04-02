CC=cc
LIBS=-lm
CFLAGS=-Wall -Wpedantic
OBJS=besselton.o astro.o

.PHONY: clean
besselton: $(OBJS)
	$(CC) $(OBJS) $(LIBS) $(CFLAGS) -o besselton
clean:
	rm -f besselton $(OBJS)
