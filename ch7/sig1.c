#include "./header.h"
#include "./header.c"

volatile sig_atomic_t usr_interrupt = 0;

void sig_usr(int sig) {
    printf("sig: %d\n", sig);
    usr_interrupt = 1;
}

void child_function() {
    printf("I'm here! My pid = %d\n", (int)getpid());
    kill(getppid(), SIGUSR1);

    puts("Bye, now....");
    exit(EXIT_SUCCESS);
}

int main() {
    pid_t child_id;
    signal(SIGUSR1, sig_usr);

    child_id = fork();
    if (child_id == 0) {
        child_function();
    }

    int x = 0;
    while (!usr_interrupt) {
        x++;
        printf("show something. x = %d\n", x);
    }

    puts("That's all!");
    
    exit(EXIT_SUCCESS);
}