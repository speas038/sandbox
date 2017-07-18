C=gcc
CFLAGS=-I.
DEPS = 
PROG = list


$(PROG): $(PROG).c
	gcc -o $@ $^ $(CFLAGS)

all: $(PROG)

clean:
	rm -f $(PROG) *.o
