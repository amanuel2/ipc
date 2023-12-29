#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/fcntl.h>
#include <sys/signal.h>
#include <unistd.h>
#include <fcntl.h>

void sigpipe_handler(int sig)  {
    printf("SIGPIPE!\n");
}


#define NAME "File2"

int main() {
    signal(SIGPIPE, sigpipe_handler);
    
    char buf[30];

    
    mknod(NAME, S_IFIFO | 0666, 0);


    printf("waiting for readers...\n");
    int fd = open(NAME, O_WRONLY);
    printf("got a reader--type some stuff\n");  


    while(gets(buf), !feof(stdin)) {
        write(fd, buf, sizeof(buf));
    }


    return 0;
}
