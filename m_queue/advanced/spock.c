#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/msg.h>
#include "headers.h"


int main() {

    struct m_buff buff;
    key_t key = ftok("/home/amanuel", 'd');
    int msg_id = msgget(key, /*IPC_CREATED_ALREADY | */ 0644);

   printf("Ready to recieve messages\n");


   for(;;) {

        msgrcv(msg_id, &buff, sizeof buff.m_val, 0, 0);
        printf("spock: \"%s\"\n", buff.m_val);
   }
    
    
   return 0;

}
