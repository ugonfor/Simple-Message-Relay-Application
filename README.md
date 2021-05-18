# Simple-Message-Relay-Application
 Implementing a Simple Message Relay Application using Socket API

## Implementation

1. The implementation part consists of a relay server and two message transfer clients.
2. Each client establishes a TCP connection to the server.
3. If both TCP connections are successfully established, the server sends a message to the clients through each connection, signaling the server is ready.
4. After receiving the ready message, the client firstly connected to the server is now receives a user-typed message and sends it to the server.
5. Then, the server relays the message to another client.
6. The relayed message is printed at another client. After this process, the sockets are closed.


## reference 

* https://www.geeksforgeeks.org/socket-programming-cc/
* https://www.binarytides.com/socket-programming-c-linux-tutorial/
* https://y0ubat.tistory.com/76