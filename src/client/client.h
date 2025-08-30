#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int send_request(const char* method, const char* host, int port, const char* path);
void test_all_requests(void);

#endif