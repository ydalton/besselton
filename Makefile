CC=cc
LIBS=-lm
CFLAGS=-Wall -Wpedantic
OBJS=besselton.o astro.o

.PHONY: clean besselton
besselton: $(OBJS)
	$(CC) $(OBJS) $(LIBS) $(CFLAGS) -o besselton
%.o: %.c
	$(CC) $(CFLAGS) $< -c
clean:
	rm -f besselton $(OBJS)
