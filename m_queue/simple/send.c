#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/msg.h>
#include "header.h"



int main() {


    key_t key = ftok("/home/amanuel2", 'b');
    int msg_id = msgget(key, IPC_CREAT | 0666); // create message queue
    
    
    struct tcp data = {
        .sport = 80,
        .dport = 90,
        .admin = "Aman",
    };

    struct tcp_buf buf = {
        .id = 2,
        .tcp = data
    };

    msgsnd(msg_id, &buf, sizeof(data), 0);
    
    return 0;
}
