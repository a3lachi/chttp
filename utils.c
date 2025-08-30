#include "utils.h"
#include <string.h>

bool is_get_request(const char* request) {
    if (request == NULL) {
        return false;
    }
    
    return strncmp(request, "GET ", 4) == 0;
}

bool is_post_request(const char* request) {
    if (request == NULL) {
        return false;
    }
    
    return strncmp(request, "POST ", 5) == 0;
}

bool is_put_request(const char* request) {
    if (request == NULL) {
        return false;
    }
    
    return strncmp(request, "PUT ", 4) == 0;
}