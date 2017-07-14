#!/bin/bash


IP="10.1.2.181"

sudo /home/alex/rump/rumprun/rumprun/bin/rumprun xen \
	-di \
    -I xen0,xenif \
    -W xen0,inet,static,10.1.2.132/24 \
    ./udp-send-rumprun 

