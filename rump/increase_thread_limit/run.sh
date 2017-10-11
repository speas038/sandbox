#!/bin/bash

IP=10.30.30.134

x86_64-rumprun-netbsd-gcc -ggdb -o test test.c
rumprun-bake xen_pv test-rumprun test


echo "gdb -tui -ex 'target remote:1234' xenevent.run"

rumprun -S xen -di -M 5120 -N test-rump \
	-I xen0,xenif \
	-W xen0,inet,static,$IP/24 \
	./test-rumprun


#sudo /home/alex/rump/rumprun/rumprun/bin/rumprun xen -di \
#	-I xen0,xenif \
#	-W xen0,inet,dhcp \
#	./test.run
