



all: helloer-rumprun timer


helloer-rumprun: helloer
	rumprun-bake xen-pv helloer-rumprun helloer



helloer: helloer.c
	x86_64-rumprun-netbsd-gcc helloer.c -o helloer

timer: timer.c
	gcc -o timer timer.c

clean:
	rm helloer-rumprun helloer timer
