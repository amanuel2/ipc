#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#define _POSIX_C_SOURCE 1




int main(int argc, char** argv) {



    pid_t pid = atoi(argv[1]);
    int val = atoi(argv[2]);

    union sigval sv;
    sv.sival_int = val;


    sigqueue(pid, SIGUSR1, sv);

    return 0;
}

