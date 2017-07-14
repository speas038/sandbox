#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>


#define PORT 1153
#define BUFSIZE 4
#define SERVICE_PORT	21234	/* hard-coded port number */

int main()
{
	struct timeval start, end, elapsed;
	
	struct sockaddr_in myaddr;	/* our address */
	struct sockaddr_in remaddr;	/* remote address */
	socklen_t addrlen = sizeof(remaddr);		/* length of addresses */
	int recvlen;			/* # bytes received */
	int fd;				/* our socket */
	int msgcnt = 0;			/* count # of messages we received */
	unsigned char buf[BUFSIZE];	/* receive buffer */

	memset( (char *)&myaddr, 0, sizeof(myaddr));

	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = htonl( INADDR_ANY );
	myaddr.sin_port = htons(0);


	gettimeofday(&start, NULL);

//	system("/home/alex/rump/startup_test/run.sh &");

	if(( fd = socket( AF_INET, SOCK_DGRAM, 0 )) < 0 )
	{
		perror("Cannot create socket");
		return 1;
	}
	
	if( bind( fd, (struct sockaddr*)&myaddr, sizeof(myaddr)) < 0){
		perror("bind failed");
		return 1;
	}

	for (;;) 
	{

		printf("waiting on port %d\n", SERVICE_PORT);
		recvlen = recvfrom(fd, buf, BUFSIZE, 0, (struct sockaddr *)&remaddr, &addrlen);
		if (recvlen > 0) {
			buf[recvlen] = 0;
			printf("received message: \"%s\" (%d bytes)\n", buf, recvlen);
		}
		else
			printf("uh oh - something went wrong!\n");

		sprintf(buf, "ack %d", msgcnt++);
		printf("sending response \"%s\"\n", buf);
		
		if (sendto(fd, buf, strlen(buf), 0, (struct sockaddr *)&remaddr, addrlen) < 0)
			perror("sendto");
		
	}
	


	gettimeofday(&end, NULL);

	timersub(&end, &start, &elapsed);

	printf("\nElapsed Seconds: %ld\n", elapsed.tv_sec);
	printf("\nElapsed Microseconds %ld\n", elapsed.tv_usec);
}



