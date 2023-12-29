#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>



int main() {

    int pfds[2];
    char buf[30];

    pipe(pfds);


    write(pfds[1],"Hello World", sizeof("Hello World"));

    sleep(1);

    read(pfds[0], buf, sizeof("Hello World"));
    printf("Read: %s\n", buf);
    return 0;

}
