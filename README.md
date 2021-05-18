# Simple-Message-Relay-Application
 Implementing a Simple Message Relay Application using Socket API

## Implementation

1. The implementation part consists of a relay server and two message transfer clients.
2. Each client establishes a TCP connection to the server.
3. If both TCP connections are successfully established, the server sends a message to the clients through each connection, signaling the server is ready.
4. After receiving the ready message, the client firstly connected to the server is now receives a user-typed message and sends it to the server.
5. Then, the server relays the message to another client.
6. The relayed message is printed at another client. After this process, the sockets are closed.

## Make
```shell
$ make 2>/dev/null
gcc -o client client.c
gcc -o server server.c
```

## How to use

#### server binary

```shell
$ ./server
usage: ./server <port>
$ ./server 1337
```

#### client binary
* client1 (first one is sender)
```shell
$ ./client
usage: ./client <IP address> <port>
$ ./client 127.0.0.1 1337
READY: You are a sender.
Send this message to receiver
```

* client2 (second one is receiver)
```shell
$ ./client
usage: ./client <IP address> <port>
$ ./client 127.0.0.1 1337
READY: You are a receiver.
Send this message to receiver
```

```
send this message to receiver
```

above message is your message.

## reference 

* https://www.geeksforgeeks.org/socket-programming-cc/
* https://www.binarytides.com/socket-programming-c-linux-tutorial/
* https://y0ubat.tistory.com/76