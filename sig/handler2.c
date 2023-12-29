#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/signal.h>
#include <unistd.h>


volatile sig_atomic_t got_usr1;



void signalhandler(int sig) {
    write(1, "HIT!\n", sizeof("HIT!\n"));
    got_usr1 = 1;
}


int main() {

    struct sigaction sa = {
        .sa_mask = 0,
        .sa_flags = 0,
        .sa_handler = signalhandler
    };


    got_usr1 = 0;
    sigaction(SIGUSR1, &sa, NULL);

    

    while (!got_usr1) {
        printf("PID %d: working hard...\n", getpid()); 
        sleep(1);
    }       

    return 0;
}
