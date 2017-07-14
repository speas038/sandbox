//
/*
    C socket server example
*/
 
#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write

#define MSG_SZ  7500
 
int main(int argc , char *argv[])
{
    int socket_desc , client_sock , c , read_size;
    struct sockaddr_in server , client;
    char client_message[MSG_SZ];
     
    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket\n");
    }
    puts("Socket created\n");
     
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8888 );
     
    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        printf("bind failed.\n");
        return 1;
    }
    printf("bind done\n");


	printf("inet_ntoa(in_addr) = %s\n", inet_ntoa(server.sin_addr));
	//close(socket_desc);
	//return 0;

    //Listen
    listen(socket_desc , 3);
     
    //Accept and incoming connection
    printf("Waiting for incoming connections...\n");
    c = sizeof(struct sockaddr_in);
     
    //accept connection from an incoming client
    client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
    if (client_sock < 0)
    {
        perror("accept failed");
        return 1;
    }
    puts("Connection accepted");
    
	int i = 0;

    //Receive a message from client
    while( (read_size = recv(client_sock , client_message , MSG_SZ , 0)) > 0 )
    {
        //Send the message back to client
        write(client_sock , client_message , strlen(client_message));
		printf("Received data: %d\n", i);
		printf("Client Message: \n %s\n\n", client_message);
		i++;
    }
     
    if(read_size == 0)
    {
        printf("Client disconnected\n");
    }
    else if(read_size == -1)
    {
        printf("recv failed\n");
    }
     
    return 0;
}
