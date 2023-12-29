#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/signal.h>
#include <unistd.h>


void signal_handler(int sig) {
    printf("Recieved SIGNAL!\n");
}



int main() {


    struct sigaction sig = {
        .sa_handler = signal_handler,
        .sa_flags = SA_RESTART,
        .sa_mask = 0
    };


    sigaction(SIGINT, &sig, NULL);


    char *s = (char*) malloc(sizeof(char)*200);

    if(fgets(s, sizeof s, stdin) == NULL) {
        perror("ERR");
    } else {
        printf("You entered %s\n", s);
    }

    
    return 0;
}


