#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/fcntl.h>
#include <string.h>
#include <unistd.h>

#define NAME "file1"

int main() {

    struct flock fl = {
        .l_type = F_WRLCK,
        .l_whence = SEEK_SET,
        .l_start = 0,
        .l_len = 0,
    };


    int fd = open(NAME, O_WRONLY);
    
    fcntl(fd, F_SETLKW, &fl);
    printf("LOCK AQUIRED\n");
    
    char *buf;
    while(buf = fgetc(stdin)) {
        if(buf == '\n') break;
        write(fd, buf, 1);
    }


    fl.l_type = F_UNLCK;
    fcntl(fd, F_SETLKW, &fl);
    printf("UNLOCKED\n");

    return 0;
}
