#include <stdio.h>
#include <signal.h>
#include <sys/signal.h>
#include <unistd.h>


void signal_handler(int sig) {
    printf("Recieved signal %d\n", sig);
}



int main() {
    struct sigaction sa;
    sigset_t set;


    sigemptyset(&set);
    //sigset(SIGINT, signal_handler);
    sigaddset(&set,SIGINT);
    

    sa.sa_handler = signal_handler;
    sa.sa_flags = 0;
    sa.sa_mask = set;


    
    while(1) {
        printf("Waiting...\n");
        sleep(1);
    }


    return 0;
}
