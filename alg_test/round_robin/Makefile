C=gcc
CFLAGS=-I.
DEPS = 
PROG = round_robin


$(PROG): $(PROG).c
	gcc -o $@ $^ $(CFLAGS)

all: $(PROG)

clean:
	rm -f $(PROG) *.o
