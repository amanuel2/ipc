#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>

int main() {

    int fd = open("foo", O_RDONLY);
    size_t pg_size = getpagesize();


    char* data = mmap(NULL, pg_size, PROT_READ, MAP_SHARED, fd, pg_size);
    printf("Data Read = %s\n", data);

    return 0;
}

