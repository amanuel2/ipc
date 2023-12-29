#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/shm.h>



int main(int argc, char**argv) {
    
    int shmid = atoi(argv[1]);
    char* data = shmat(shmid, NULL , 0);
    printf("Enter a string: ");
    fgets(data, 4096, stdin);

    return 0;
}
