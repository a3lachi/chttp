# HTTP Server in C

A simple HTTP server implementation written in C.



## Project Structure

- `server.c` - Main HTTP server implementation
- `Makefile` - Build configuration


## Building

To compile the server:

```bash
make
```

## Running

To start the HTTP server:

```bash
./server
```

## Cleaning

To remove built files:

```bash
make clean
```

## How It Works

The server implements a basic HTTP server using TCP sockets:

1. **Socket Creation**: Creates a TCP socket using `socket(AF_INET, SOCK_STREAM, 0)`
2. **Binding**: Binds to port 8080 on all interfaces (`INADDR_ANY`)
3. **Listening**: Listens for incoming connections with a backlog of 10
4. **Accept Loop**: Continuously accepts client connections in an infinite loop
5. **Request Processing**: 
   - Reads incoming HTTP requests into a 4KB buffer
   - Prints the request to stdout for debugging
   - Responds with a simple "Hello, world!" message
6. **Response Format**: Sends proper HTTP/1.1 response with:
   - Status: `200 OK`
   - Content-Type: `text/html`
   - Content-Length: `13`
   - Body: `Hello, world!`
7. **Connection Cleanup**: Closes each client connection after sending response

## Features

- Single-threaded synchronous server
- Fixed "Hello, world!" response to all requests
- Request logging to console
- Port 8080 binding
- Proper HTTP/1.1 response headers

## Requirements

- GCC compiler
- Standard C library