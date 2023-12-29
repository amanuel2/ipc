#ifndef HEADER_C
#define HEADER_C
#include <stdint.h>

struct tcp_buf {
    long id;

    struct tcp {
        uint16_t sport;
        uint16_t dport;
        char admin[10];
    } tcp;
};

#endif
