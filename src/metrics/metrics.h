#ifndef METRICS_H
#define METRICS_H

#include <time.h>

typedef struct {
    struct timespec start_time;
    struct timespec end_time;
    double duration_ms;
} request_metrics_t;

void metrics_start_request(request_metrics_t* metrics);
void metrics_end_request(request_metrics_t* metrics);
void metrics_print_request_time(const request_metrics_t* metrics, const char* method);

#endif