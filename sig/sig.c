#include <stdlib.h>
#include <stdio.h>
#include <sys/signal.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>



void advancedSignalHandler(int signo, siginfo_t *info, void *context) {
    printf("Signal Number: %d\n", info->si_signo);
    printf("Error Number: %d\n", info->si_errno);
    printf("Signal Code: %d\n", info->si_code);
    printf("Sending Process ID: %d\n", info->si_pid);
    printf("User ID of Sender: %d\n", info->si_uid);
    printf("Exit Value or Signal: %d\n", info->si_status);
    printf("Fault Address: %p\n", info->si_addr);
    printf("Signal Value: %d\n", info->si_value.sival_int);  // assuming int value
    printf("Band Event: %ld\n", info->si_band);
}


int main() {

    struct sigaction sa = {
        .sa_mask = 0,
        .sa_flags = SA_SIGINFO,
        .sa_sigaction = advancedSignalHandler
    };

    sigemptyset
    sigaction(SIGINT, &sa, NULL);
    

    return 0;
}
