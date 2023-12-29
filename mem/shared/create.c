#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/shm.h>

void sig_handler(int sig) {
    printf("EXITING!\n");
    // thought detaching was possible here
}

int main() {

    key_t key = ftok("/home/amanuel2", 'd');
    int shmid = shmget(key, 4096, IPC_CREAT | 0666);
    
    void* data = shmat(shmid, NULL, 0);
    
    if(data == (void*)-1) perror("error creating shm");

    printf("Created shm with id: %d\n", shmid);
    while(1){};

}
