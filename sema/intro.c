#include <stdio.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
#include <unistd.h>


/*
 
    int semctl(int semid, int semnum, int cmd, ... // args );
    
    ------  args -----
    union semun {
	    int val; // used for SETVAL only 
	    struct semid_ds *buf; // used for IPC_STAT and IPC_SET
	    ushort *array; // used for GETALL and SETALL
    };

    struct semid_ds {
        struct ipc_perm sem_perm; // Ownership and permissions 
        time_t sem_otime; // Last semop time
        time_t sem_ctime; // Last change time 
        unsigned short sem_nsems; // No. of semaphores in set
    };


  cmd 			|		Effect
 -------------------------------
  SETVAL		| Set the value of the specified semaphore to the value in the val member of the passed-in union semun.

  GETVAL		| Return the value of the given semaphore.
  SETALL		| Set the values of all the semaphores in the set to the values in the array pointed to by the array member of the passed-in union semun. The semnum parameter to semctl() isn’t used.
  GETALL 		| Gets the values of all the semaphores in the set and stores them in the array pointed to by the array member of the passed-in union semun. The semnum parameter to semctl() isn’t used.

 IPC_RMID		| Remove the specified semaphore set from the system. The semnum parameter is ignored.
 IPC_STAT		|  Load status information about the semaphore set into the struct semid_ds structure pointed to by the buf member of the union semun.

    
    

    int semop(int semid, struct sembuf *sops, unsigned int nsops);

    ------- sembuf ----
    All operations that set, get, or test-n-set a semaphore use the semop() system call. 
    This system call is general purpose, and its functionality is dictated by a structure 
    that is passed to it, struct sembuf:
    
    struct sembuf { 
        ushort sem_num;
        short sem_op;
        short sem_flg; 
    };



*/

#define MAX_RETRIES 10


int init_sema(int num) {

    union semun args;
    struct semid_ds ds;
    struct sembuf sb;

    key_t key = ftok("/home/amanuel", 'd');
    int sem = semget(key, num, IPC_CREAT | 0666);
    
    if(sem>=0) { // we got there first
        
        sb.sem_flg = 0;
        sb.sem_op = 1;
        args.val = 1;
        
        printf("Press any char\n"); getchar();

        for(sb.sem_num = 0; sb.sem_num < num; sb.sem_num++) { 
            
            if(semop(sem, &sb, 1) == -1) {
                int e = errno;
                semctl(sem, 0, IPC_RMID);
                errno = e;
                return -1;
            }

        }

    } else if(errno == EEXIST) { // someone got here
        
        sem = semget(key, num, 0);
        if(sem<0) return errno;
        
        args.buf = &ds;
        for(int i = 0; i < MAX_RETRIES; i++) {
            semctl(sem, num, IPC_STAT, args);
            if(args.buf->sem_otime != 0) {
                break;
            } else {
                sleep(1);
            }
        }
        
        printf("Group ID: %d , User ID: %d\n", args.buf->sem_perm.gid, args.buf->sem_perm.uid);

    } else {
        return errno;
    }

    return sem;
}

int main() {
    
    char buf[10];
    int semid = init_sema(100);
    printf("Semaphore ID: %d", semid);

    
    printf("press any char to lock: \n"); 
    fgets(buf, sizeof(buf), stdin);

    struct sembuf sb; 
    sb.sem_num = 0;
    sb.sem_op = -1; /* set to allocate resource */ 
    sb.sem_flg = SEM_UNDO;
    semop(semid, &sb, 1);
    printf("LOCKED\n");    

    printf("press any char to unlock: \n");
    fgets(buf, sizeof(buf), stdin);
    sb.sem_op = 1;
    semop(semid, &sb, 1);
    printf("UNLOCKED\n");

    return 0;
}



