#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
 
#define BUF_SIZE 1024

int main(int argc, char const *argv[])
{
    // server MUST take one command-line arguments
    if (argc != 2) {
        printf("usage: %s <port>\n", argv[0]);
        return 1;
    }

    // Argument1 : Server port number 
    char* server_port = argv[1];

    // server permits two TCP clients.
    int server_fd, client1_fd, client2_fd; // socket descriptor of server, client1, client2
    struct sockaddr_in server_addr, client1_addr, client2_addr;  // socket address of server, client1, client2

    char recv_data[BUF_SIZE]; // receive data buffer 
    char send_data[BUF_SIZE]; // send data buffer
    
    // accept ft needs address size pointer
    int client1_len = sizeof(client1_addr); // address size
    int client2_len = sizeof(client2_addr); // address size 

    // create socket 
    // AF_INET : IPv4
    // SOCK_STREAM : TCP
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1)
    {
        // if occur creation error
        puts("socket creation error");
        return 1;
    }

    // set the server address from arguments
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); // server ip. INADDR_ANY : use ALL LAN card.
    server_addr.sin_family = AF_INET; // IPv4
    server_addr.sin_port = htons(atoi(server_port)); // port number

    // bind socket to server_addr
    // server_addr's IP : INADDR_ANY. so It binds the socket to all available interfaces.
    if(bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
    {
        // if occur bind error
        puts("bind error");
        return 1;
    }

    // listen connection from clients
    if(listen(server_fd, 5) < 0)
    {
        // if occur listen error
        puts("listen error");
        return 1;
    }

    // clear the recv_data, send_data buffers
    memset(recv_data, 0, sizeof(recv_data));
    memset(send_data, 0, sizeof(send_data));

    // accept connection from clients
    client1_fd = accept(server_fd,(struct sockaddr *)&client1_addr,(socklen_t *)&client1_len);
    client2_fd = accept(server_fd, (struct sockaddr*)&client2_addr, (socklen_t *)&client2_len);

    // handle the accept error
    if(client1_fd < 0)
    {
        puts("client 1 accept failed\n");
        exit(0);
    }
    if(client2_fd < 0)
    {
        puts("client 2 accept error\n");
        exit(0);
    }
    
    // For debug, print the client ip address.
    char ip_addr_clients[20];
    inet_ntop(AF_INET, &client1_addr.sin_addr.s_addr, ip_addr_clients, sizeof(ip_addr_clients));
    // printf("%s client connect.\n", ip_addr_clients);
    
    inet_ntop(AF_INET, &client2_addr.sin_addr.s_addr, ip_addr_clients, sizeof(ip_addr_clients));
    // printf("%s client connect.\n", ip_addr_clients);

    // send the message to clients after the two different TCP connections are made.
    send(client1_fd, "READY: You are a sender.", 25, 0);
    send(client2_fd, "READY: You are a receiver.", 27, 0);

    // recv the message from sender client.
    recv(client1_fd, recv_data, BUF_SIZE, 0);

    // move the data from recv_data to send_data
    memcpy(send_data, recv_data, strnlen(recv_data, BUF_SIZE-1));

    // send the message to receiver client.
    send(client2_fd, send_data, strnlen(send_data, BUF_SIZE-1)+1, 0);
    
    // after the relay, close the socket descriptors.
    close(client1_fd);
    close(client2_fd);

    // close the server's socket descriptors
    close(server_fd);

	return 0;
}
