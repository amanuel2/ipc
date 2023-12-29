#include <stdlib.h>
#include <stdio.h>
#include <sys/_types/_s_ifmt.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <fcntl.h>


#define FILE_NAME "File2"

int main() {
    

    mknod(FILE_NAME, S_IFIFO | 0666, NULL);
    
    printf("Waiting writers...\n");
    int fd = open(FILE_NAME, O_RDONLY);
    printf("Got a writer... \n");
    
    
    int bytes = 0;
    char s[20];
    do {
        bytes = read(fd, s, sizeof(s));
        printf("tick: read %d bytes: \"%s\"\n", bytes, s);
    } while(bytes>0);


    return 0;
}
