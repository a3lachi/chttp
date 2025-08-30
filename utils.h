#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

bool is_get_request(const char* request);
bool is_post_request(const char* request);
bool is_put_request(const char* request);

#endif