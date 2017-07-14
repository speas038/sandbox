



all: udp-send-rumprun udp-recv

udp-send-rumprun: udp-send
	rumprun-bake xen-pv udp-send-rumprun udp-send
	rm udp-send

udp-send: udp-send.c 
	x86_64-rumprun-netbsd-gcc udp-send.c -o udp-send


udp-recv: udp-recv.c 
	gcc -o udp-recv udp-recv.c


clean:
	rm -f udp-send udp-send-rumprun udp-recv
