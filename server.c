#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server_fd, client_fd;
    struct sockaddr_in addr;
    char buffer[4096];
    
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = INADDR_ANY;
    
    bind(server_fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 10);

    printf("Server running on http://localhost:8080\n");

    while (1) {
        client_fd = accept(server_fd, NULL, NULL);
        read(client_fd, buffer, sizeof(buffer));
        printf("Request:\n%s\n", buffer);

        char response[] =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n"
            "Content-Length: 13\r\n"
            "\r\n"
            "Hello, world!";

        write(client_fd, response, sizeof(response)-1);
        close(client_fd);
    }

    return 0;
}
