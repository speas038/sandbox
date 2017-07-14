##
## NOTICE: If you compiled rump from a git branch, the rump binaries
## were put into a directory whose name is branch-dependent. Adjust
## your PATH accordingly.
##

export PATH := /home/alex/rump/rumprun/./rumprun/bin:$(PATH)

CC=x86_64-rumprun-netbsd-gcc
MATH=-lm
CFLAGS= -ggdb

BAKE=rumprun-bake
BAKEFLAGS=xen_pv


all: echo_server-rumprun.run echo_client-rumprun.run


echo_server-rumprun.run: echo_server-rumprun
	$(BAKE) $(BAKEFLAGS) echo_server-rumprun.run echo_server-rumprun
	rm echo_server-rumprun
	
echo_server-rumprun: echo_server.c
	$(CC) $(CFLAGS) echo_server.c -o echo_server-rumprun

echo_client-rumprun.run: echo_client-rumprun
	$(BAKE) $(BAKEFLAGS) echo_client-rumprun.run echo_client-rumprun
	rm echo_client-rumprun

echo_client-rumprun: echo_client.c
	$(CC) $(CFLAGS) echo_client.c $(MATH) -o echo_client-rumprun

clean : 
	rm *-rumprun.run 
