#!/bin/bash


#Need to sleep or something because trying to start the rump kernel 
#before the old one has started results in a failure

IP="10.1.2.18"

#clear log file


for i in `seq 0 3`;
do
	printf "$i	"
	/usr/bin/time -f "time: %e" \
		rumprun -S xen \
			-d -M 16 \
			-I xen0,xenif \
			-W xen0,inet,static,$IP/24 \
          	./helloer-rumprun \
#		2>&1 \
#		| grep "time:" \
#		| awk '{print $2}' 

	while  sudo xl list | grep rumprun > /dev/null; 
	do
		:
	done

done

exit 0
