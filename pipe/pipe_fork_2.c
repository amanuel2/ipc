#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/_types/_sigset_t.h>
#include <unistd.h>


void signal_handler (int sig) {
    printf("HIT\n");
}

int main() {
    
    int pfds[2];

//    pipe(pfds);

//    if(!fork()) {
//        // Child
//        close(1);
//        dup(pfds[1]);
//        write(pfds[1], "Hii", sizeof("Hii"));
//    } else {
//        close(0);
//        dup(pfds[0]);
//        
//        char buf[30];
//        read(pfds[0], buf, sizeof(buf)); 
//    }
    

    sigset_t st;
    sigemptyset(&st);
    sigaddset(&st, SIGINT);
    
    struct sigaction sa;
    sa.sa_mask = st;
    sa.sa_flags = 0;
    sa.sa_handler = signal_handler;


    pipe(pfds);
    
    if(!fork()) {
        close(0);
        dup(pfds[0]);
        execlp("ls", "ls", NULL);
    } else {
        close(1);
        dup(pfds[1]);
        execlp("wc", "wc", "-l", NULL);
    }

    

    return 0;
    
}
