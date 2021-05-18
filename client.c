#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

#define BUF_SIZE 1024

int main(int argc, char const *argv[])
{
    // client MUST take two command-line arguments
    if (argc != 3) {
        printf("usage: %s <IP address> <port>\n", argv[0]);
        return 1;
    }

    // Argument1 : Server IP address 
    char* server_ip = argv[1];
    // Argument2 : Server Port
    char* server_port = argv[2];

    int socket_fd; // socket descriptor
    struct sockaddr_in server_addr; // server socket address
    char recv_data[BUF_SIZE]; // receive data buffer 
    char send_data[BUF_SIZE]; // send data buffer

    // create socket 
    // AF_INET : IPv4
    // SOCK_STREAM : TCP
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd == -1)
    {
        // if occur creation error
        puts("socket creation error");
        return 1;
    }

    // set the server address from arguments
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_addr.s_addr = inet_addr(server_ip); // server ip
    server_addr.sin_family = AF_INET; // IPv4
    server_addr.sin_port = htons(atoi(server_port)); // port number

    // TCP connection with server
    if(connect(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        // if occur connection error
        puts("connect error\n");
        close(socket_fd);
        return 1;
    }

    // recv message from server    
    memset(recv_data, 0, BUF_SIZE);
    recv(socket_fd, recv_data, sizeof(recv_data), 0);
    printf("%s\n", recv_data);

    // If the client receives the server’s message “READY: You are a sender.”,
    if (strcmp("READY: You are a sender.", recv_data) == 0)
    {
        // it immediately takes user’s message from the standard input
        memset(send_data, 0, BUF_SIZE);
        fgets(send_data, BUF_SIZE-1, stdin);

        // sends the message to the server
        send(socket_fd, send_data, strnlen(send_data, BUF_SIZE), 0);
    }
    // if the message from the server is “READY: You are a receiver.”, the client
    else
    {
        // should wait for another message (a relayed message) from the server. 
        memset(recv_data, 0, BUF_SIZE);
        recv(socket_fd, recv_data, BUF_SIZE-1, 0);

        // the client prints it to the standard output and terminates
	    printf("%s", recv_data);
    }
    
    // close socket descriptor
    close(socket_fd);

    return 0;
}
