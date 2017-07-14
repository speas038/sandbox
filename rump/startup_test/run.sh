#!/bin/bash


IP="10.1.2.18"

sudo /home/alex/rump/rumprun//rumprun/bin/rumprun xen \
	-di \
    -I xen0,xenif \
    -W xen0,inet,static,$IP/24 \
    ./helloer-rumprun \

