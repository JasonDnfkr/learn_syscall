#include "./header.h"
#include "./header.c"

int zero = 0;

int main() {
    pid_t pid;
    int status;

    if ((pid = fork()) == 0) {
        exit(EXIT_SUCCESS);
    }
    if ((pid = fork()) == 0) {
        abort();
    }
    if ((pid = fork()) == 0) {
        status /= zero;
        exit(EXIT_SUCCESS);
    }

    while ((pid = wait(&status)) >= 0) {
        pr_exit(status, pid);
    }

    perror("wait over");

    exit(EXIT_SUCCESS);
}