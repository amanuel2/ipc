#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>

int main() {
    int sock;
    assert( (sock = socket(AF_UNIX, SOCK_STREAM, 0)) != -1);
    
    struct sockaddr_un local = {
        .sun_path = "/Users/aboga/socket",
        .sun_family = AF_UNIX
    };
    
    unlink(local.sun_path);
    int len = strlen(local.sun_path) + sizeof(local.sun_family); 
    
    assert(bind(sock, (struct sockaddr*) &local, len) != -1);

    
    // listen for client connections
    listen(sock, 5); // 5 max connections (backlog) before ERR_CONREFUSED

    len = sizeof(struct sockaddr_un);

    int acc;
    printf("Waiting for a connection...\n");
    assert( (acc = accept(sock, (struct sockaddr*) &local, &len)) != -1); // fd for accepted socket
    printf("Connected!\n");
    
    char buf[256];
    while (len = recv(acc, &buf, 256, 0), len>0) {
        for(int i=0; i<256; i++) buf[i] = toupper(buf[i]);
        assert(send(acc, &buf, 256, 0) != -1);
    }

    close(acc);
    
}
