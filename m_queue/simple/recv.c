
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
    
    struct tcp_buf recv_buf; 
    

    msgrcv(msg_id, &recv_buf, sizeof(struct tcp_buf), 2, 0);

    
    printf("Source: %d, Dest: %d, ID: %s", recv_buf.tcp.sport, recv_buf.tcp.dport, recv_buf.tcp.admin);

    return 0;
}
