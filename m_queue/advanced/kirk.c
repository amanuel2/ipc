#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/msg.h>
#include "headers.h"


int main() {

    key_t key = ftok("/home/amanuel", 'd');
    int msg_id = msgget(key, IPC_CREAT | 0644);
    
    printf("Enter Lines: \n");

    struct m_buff buf = {
        .m_type = 1
    };


    while (fgets(buf.m_val, sizeof buf.m_val, stdin) != NULL) {
        int n = sizeof buf.m_val;
        buf.m_val[n-1] = '\0';
        msgsnd(msg_id, &buf, n, 0);
    }
    

    msgctl(msg_id, IPC_RMID, NULL);
    return 0;
}
