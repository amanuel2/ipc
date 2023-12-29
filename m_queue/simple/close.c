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
    
    struct msqid_ds buf;
    msgctl(msg_id, IPC_STAT, &buf);
    
    printf("Message Queue ID: %d\n", msg_id);
    printf("Time of last msgsnd: %ld\n", buf.msg_stime);
    printf("Time of last msgrcv: %ld\n", buf.msg_rtime);
    printf("Time of last change: %ld\n", buf.msg_ctime);
    printf("Current number of bytes in queue: %ld\n", buf.msg_cbytes);
    printf("Current number of messages in queue: %ld\n", buf.msg_qnum);
    printf("Maximum number of bytes allowed in queue: %ld\n", buf.msg_qbytes);
    printf("PID of last msgsnd: %d\n", buf.msg_lspid);
    printf("PID of last msgrcv: %d\n", buf.msg_lrpid);
    printf("Key supplied to msgget(2): %d\n", buf.msg_perm._key);
    printf("Effective UID of owner: %d\n", buf.msg_perm.uid);
    printf("Effective GID of owner: %d\n", buf.msg_perm.gid);
    printf("Permissions: %o\n", buf.msg_perm.mode);




    printf("CLOSING!\n");
    msgctl(msg_id, IPC_RMID, NULL); 

    return 0;
}
