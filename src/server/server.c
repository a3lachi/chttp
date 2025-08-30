#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "utils.h"

int main() {
    int server_fd, // server's socket file descriptor
        client_fd; // new socket created when a client connects
    struct sockaddr_in addr; // stores IP + port configuration for the server.
    char buffer[4096]; // where we’ll store the client’s HTTP request
    
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0))<0) {
        perror("Socket creation failed!");
        exit(EXIT_FAILURE);
    } // creates a network socket, AF_INET → IPv4, SOCK_STREAM → TCP, 0 → default protocol (TCP)

    // config socket : setup addr
    addr.sin_family = AF_INET; // AF_INET → using IPv4
    addr.sin_port = htons(8080); // port 8080
    addr.sin_addr.s_addr = INADDR_ANY; // listen on all interfaces (0.0.0.0)

    if (bind(server_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("Couldn't bind socket with address!");
        exit(EXIT_FAILURE);
    } // associates the socket with our IP:port
    // At this point, the OS knows: “If someone connects to port 8080, send it to this socket.”
    
    if (listen(server_fd, 10) < 0 ) {
        perror("Listening failed!");
        exit(EXIT_FAILURE);
    } // Tells the OS to start listening for incoming connections.
    // 10 = backlog (how many clients can queue while waiting).

    printf("Server running on http://localhost:8080\n"); // we know now server is live

    while (1) { // Infinite loop → handle multiple clients.
        if ((client_fd = accept(server_fd, NULL, NULL))<0) {
            perror("Accept failure!");
            continue;
        } // accept blocks until a client connects and return a new socket just for the client
        read(client_fd, buffer, sizeof(buffer)); // get the HTTP request into buffer
        
        // printf("Request:\n%s\n", buffer); 

        if (is_get_request(buffer)) {
            printf("== SERVER RECEIVED A GET REQUEST\n");
            char response[] =          // raw HTTP response
                "HTTP/1.1 200 OK\r\n"   // status line
                "Content-Type: text/html\r\n"   // headers
                "Content-Length: 22\r\n"
                "\r\n"
                "You sent a GET request";   // body 
            printf("%s\n",response);
            ssize_t bytes_written = write(client_fd, response,
            sizeof(response)-1);
            if (bytes_written == -1) {
                perror("Write failed");
            } else {
                printf("%d written.\n",bytes_written);
            }
        } else if (is_post_request(buffer)) {
            printf("== SERVER RECEIVED A POST REQUEST\n");
            char response[] =          // raw HTTP response
                "HTTP/1.1 200 OK\r\n"   // status line
                "Content-Type: text/html\r\n"   // headers
                "Content-Length: 22\r\n"
                "\r\n"
                "You sent a POST request";   // body 
            write(client_fd, response, sizeof(response)-1);
        } else if (is_put_request(buffer)) {
            printf("== SERVER RECEIVED A PUT REQUEST\n");
            char response[] =          // raw HTTP response
                "HTTP/1.1 200 OK\r\n"   // status line
                "Content-Type: text/html\r\n"   // headers
                "Content-Length: 20\r\n"
                "\r\n"
                "You sent a PUT request";   // body 
            write(client_fd, response, sizeof(response)-1);
        } else {
            printf("== SERVER RECEIVED AN UNKNOWN REQUEST\n");
            char response[] =          // raw HTTP response
                "HTTP/1.1 200 OK\r\n"   // status line
                "Content-Type: text/html\r\n"   // headers
                "Content-Length: 24\r\n"
                "\r\n"
                "You sent an unknown request";   // body 
            write(client_fd, response, sizeof(response)-1);
        }
        
        close(client_fd);  // closes the connection
    }


    return 0;
}
