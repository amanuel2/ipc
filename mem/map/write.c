#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>



int main() {

    int fd = open("foo2", O_RDWR);
    if(fd == -1) perror("Error opening file");
    size_t pg_size = getpagesize();
    
    ftruncate(fd, pg_size); // Ensure the file is the right size

    //char* data = (char*) mmap((void*)0, pg_size, PROT_WRITE, MAP_SHARED, fd, pg_size);
    char* data = (char*) mmap(NULL, pg_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (data == MAP_FAILED) {
        perror("Error mapping memory");
        close(fd);
        return EXIT_FAILURE;
    }


    printf("Write your stuff(%ld): ", pg_size);
    fgets(data, pg_size, stdin);

    return 0;
}
