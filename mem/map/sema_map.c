#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/semaphore.h>
#include <unistd.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <assert.h>

struct mmapbuf {

    sem_t sem_child;
    sem_t sem_par;
    
    size_t cnt;
    char buf[256];
    
};

int main(int argc, char** argv) {

    assert(argc>=2);
    char* str = argv[1];


    void* shared_mem = mmap(NULL, sizeof(struct mmapbuf), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if(shared_mem == MAP_FAILED) perror("Couldn't provide mapping\n");


    struct mmapbuf* shm = (struct mmapbuf*) shared_mem;
    
    assert(sem_init(&shm->sem_child, 1, 0) != -1);
    assert(sem_init(&shm->sem_par, 1, 0) != -1);
    

    pid_t child_pid = fork();

    if(!child_pid) {
        
        assert(sem_wait(&shm->sem_child) != -1); // wait for parent to fill

        for(int i=0; i<shm->cnt; i++) shm->buf[i] = toupper(shm->buf[i]);

        assert(sem_post(&shm->sem_par) != -1); // reply to parent

    } else { // in parent
             
        shm->cnt = strlen(str);
        memcpy(shm->buf, str, shm->cnt);

        assert(sem_post(&shm->sem_child) != -1);
        assert(sem_wait(&shm->sem_par) != -1);
        
        printf("Result: %s\n", shm->buf);
        waitpid(child_pid, NULL, 0);

    }

    return 0;
}
