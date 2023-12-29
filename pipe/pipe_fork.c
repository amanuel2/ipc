#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>



int main() {
    
    int pfds[2];

    pipe(pfds);

    if(!fork()) {
        // Child
        sleep(1);
        write(pfds[1], "Hii", sizeof("Hii"));
    } else {
        
        char buf[30];
        read(pfds[0], buf, sizeof(buf)); 
        printf("Read %s\n", buf);
    }


    return 0;
    
}
