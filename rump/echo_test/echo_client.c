/*
* Echo Client    
*/
#include <math.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>

#define SRVR_MSG_SZ  7500
#define BUF_SZ       7500

#define msg_str      "hell"

int sock;
struct sockaddr_in server;
char message[BUF_SZ] , server_reply[SRVR_MSG_SZ];

void init();
double run_test(int);
void tear_down();

int main(int argc , char *argv[])
{
	int i = 0;
	double time_spent = 0.0;
	
	
	
    init();

	for ( i = 0; i < 1000; i++ )
	{
		time_spent = run_test( i );
		
		printf("time: %d    %lf\n", i, time_spent);
	}


	tear_down();
    
    return 0;
}

double run_test(int iterations)
{
	struct timeval start = {0};
	struct timeval end = {0};
	struct timeval elapsed = {0};
	int i = 0;

	gettimeofday(&start, NULL);

    memset(message, 0, BUF_SZ);
    memset(message, 65, BUF_SZ - 1);
    
	// Echo back and forth with server 
    for(i = 0; i < iterations; i++)
    {
         
        // Send the message 
        if( send(sock , message , strlen(message) , 0) < 0)
        {
            printf("Send failed\n");
            exit(1);
        }
         
        // Receive reply
        if( recv(sock , server_reply , SRVR_MSG_SZ, 0) < 0)
        {
            printf("recv failed\n");
            break;
        }
    }

	gettimeofday(&end, NULL);

	timersub(&end, &start, &elapsed);

	return elapsed.tv_sec + elapsed.tv_usec/1000000.0;

}

void init()
{
    sock = socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
    if (sock < 0)
    {
        printf("Could not create socket\n");
        exit(1);
    }
    printf("Socket created\n");
     
    server.sin_addr.s_addr = inet_addr("10.1.2.132");
    server.sin_family = AF_INET;
    server.sin_port = htons( 8888 );
 
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        printf("connect failed. Error");
        exit(1);
    }
     
    printf("Connected\n");

}


void tear_down()
{
	close(sock);
}
