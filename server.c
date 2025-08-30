#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server_fd, // server's socket file descriptor
        client_fd; // new socket created when a client connects
    struct sockaddr_in addr; // stores IP + port configuration for the server.
    char buffer[4096]; // where we’ll store the client’s HTTP request
    
    server_fd = socket(AF_INET, SOCK_STREAM, 0);  // creates a network socket, AF_INET → IPv4, SOCK_STREAM → TCP, 0 → default protocol (TCP)
    if (server_fd>-1) { // if network socket is created
        addr.sin_family = AF_INET; // AF_INET → using IPv4
        addr.sin_port = htons(8080); // port 8080
        addr.sin_addr.s_addr = INADDR_ANY; // listen on all interfaces (0.0.0.0)

        bind(server_fd, (struct sockaddr*)&addr, sizeof(addr)); // associates the socket with our IP:port
        // At this point, the OS knows: “If someone connects to port 8080, send it to this socket.”
        
        listen(server_fd, 10); // Tells the OS to start listening for incoming connections.
        // 10 = backlog (how many clients can queue while waiting).

        printf("Server running on http://localhost:8080\n"); // we know now server is live

        while (1) { // Infinite loop → handle multiple clients.
            client_fd = accept(server_fd, NULL, NULL); // accept blocks until a client connects and return a new socket just for the client
            read(client_fd, buffer, sizeof(buffer)); // get the HTTP request into buffer
            
            printf("Request:\n%s\n", buffer); 

            char response[] =          // raw HTTP response
                "HTTP/1.1 200 OK\r\n"   // status line
                "Content-Type: text/html\r\n"   // headers
                "Content-Length: 13\r\n"
                "\r\n"
                "Hello, world!";   // body 

            write(client_fd, response, sizeof(response)-1);  // sends the response to the client
            close(client_fd);  // closes the connection
        }

    } else {
        printf("Failed to create network socket.\n"); // socket() returns -1 if network socket failed to be created
    }
    

    return 0;
}
