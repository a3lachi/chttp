# HTTP Server in C

A simple HTTP server implementation written in C.



## Project Structure

```
src/
├── server/
│   └── server.c     - Main HTTP server implementation
├── utils/
│   ├── utils.h      - HTTP request parsing utilities header
│   └── utils.c      - HTTP request parsing utilities implementation
└── client/
    ├── client.h     - Test client header
    └── client.c     - Test client implementation
Makefile             - Build configuration
```

## Building

To compile both server and client:

```bash
make all
```

To compile only the server:

```bash
make server
```

To compile only the client:

```bash
make client
```

## Running

To start the HTTP server:

```bash
./server
```

To test the server (run in separate terminal):

```bash
./client
```

## Cleaning

To remove built files:

```bash
make clean
```

## How It Works

The server implements a basic HTTP server using TCP sockets with request type detection:

1. **Socket Creation**: Creates a TCP socket using `socket(AF_INET, SOCK_STREAM, 0)`
2. **Binding**: Binds to port 8080 on all interfaces (`INADDR_ANY`)
3. **Listening**: Listens for incoming connections with a backlog of 10
4. **Accept Loop**: Continuously accepts client connections in an infinite loop
5. **Request Processing**: 
   - Reads incoming HTTP requests into a 4KB buffer
   - Uses utility functions to detect request type (GET, POST, PUT)
   - Logs request type to server console
6. **Response Generation**: Sends different responses based on request type:
   - GET: "You sent a GET request" (21 bytes)
   - POST: "You sent a POST request" (22 bytes)
   - PUT: "You sent a PUT request" (20 bytes)
   - Unknown: "You sent an unknown request" (24 bytes)
7. **Response Format**: Sends proper HTTP/1.1 response with:
   - Status: `200 OK`
   - Content-Type: `text/html`
   - Dynamic Content-Length matching message
8. **Connection Cleanup**: Closes each client connection after sending response

## Features

- Single-threaded synchronous server
- Dynamic responses based on HTTP method (GET, POST, PUT, others)
- Request type detection using utility functions
- Request logging to console with method identification
- Port 8080 binding
- Proper HTTP/1.1 response headers
- Test client for automated testing

## Requirements

- GCC compiler
- Standard C library