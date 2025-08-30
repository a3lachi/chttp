#include "metrics.h"
#include <stdio.h>

void metrics_start_request(request_metrics_t* metrics) {
    if (metrics == NULL) {
        return;
    }
    clock_gettime(CLOCK_MONOTONIC, &metrics->start_time);
}

void metrics_end_request(request_metrics_t* metrics) {
    if (metrics == NULL) {
        return;
    }
    
    clock_gettime(CLOCK_MONOTONIC, &metrics->end_time);
    
    double start_ms = metrics->start_time.tv_sec * 1000.0 + metrics->start_time.tv_nsec / 1000000.0;
    double end_ms = metrics->end_time.tv_sec * 1000.0 + metrics->end_time.tv_nsec / 1000000.0;
    
    metrics->duration_ms = end_ms - start_ms;
}

void metrics_print_request_time(const request_metrics_t* metrics, const char* method) {
    if (metrics == NULL || method == NULL) {
        return;
    }
    
    printf("== %s request completed in %.3f ms\n", method, metrics->duration_ms);
}