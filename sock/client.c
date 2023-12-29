#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>


#define SIZE 256

int main() {
    int sock;
    assert( (sock = socket(AF_UNIX, SOCK_STREAM, 0)) != -1);
    
    struct sockaddr_un server = {
        .sun_path = "/Users/aboga/socket",
        .sun_family = AF_UNIX
    };
    
    
    printf("Connecting..\n");
    
    size_t len = strlen(server.sun_path) + sizeof(server.sun_family);
    assert(connect(sock, (struct sockaddr*) &server, len) != -1);

    printf("Connected!\n");

   
    char buf[256];
    while(printf("> "), fgets(buf, sizeof(buf), stdin), !feof(stdin)) {
        assert(send(sock, &buf, 256, 0) != -1);

        if((len = recv(sock, &buf, 256, 0)) == 0) {
            printf("CLOSED!");
            close(sock);
            exit(EXIT_SUCCESS);
        } else {
            buf[len] = '\0';
            printf("echo> %s", buf);
        }
    }


    close(sock);
    return 0;
}
