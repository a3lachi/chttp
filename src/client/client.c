#include "client.h"

int send_request(const char* method, const char* host, int port, const char* path) {
    int sock;
    struct sockaddr_in server_addr;
    char request[1024];
    char response[4096];
    
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        return -1;
    }
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    
    if (inet_pton(AF_INET, host, &server_addr.sin_addr) <= 0) {
        perror("Invalid address");
        close(sock);
        return -1;
    }
    
    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(sock);
        return -1;
    }
    
    snprintf(request, sizeof(request), 
        "%s %s HTTP/1.1\r\n"
        "Host: %s:%d\r\n"
        "Connection: close\r\n"
        "\r\n", 
        method, path, host, port);
    
    if (send(sock, request, strlen(request), 0) < 0) {
        perror("Send failed");
        close(sock);
        return -1;
    }
    
    printf("=== Sent %s request ===\n", method);
    printf("%s\n", request);
    
    ssize_t bytes_received = recv(sock, response, sizeof(response) - 1, 0);
    if (bytes_received < 0) {
        perror("Receive failed");
    } else {
        response[bytes_received] = '\0';
        printf("=== Server Response ===\n");
        printf("%s\n\n", response);
    }
    
    close(sock);
    return 0;
}

void test_all_requests(void) {
    const char* host = "127.0.0.1";
    int port = 8080;
    const char* path = "/";
    
    printf("Testing HTTP server at %s:%d\n\n", host, port);
    
    printf("1. Testing GET request:\n");
    send_request("GET", host, port, path);
    
    printf("2. Testing POST request:\n");
    send_request("POST", host, port, path);
    
    printf("3. Testing PUT request:\n");
    send_request("PUT", host, port, path);
    
    printf("4. Testing unknown request:\n");
    send_request("DELETE", host, port, path);
}

int main(void) {
    test_all_requests();
    return 0;
}