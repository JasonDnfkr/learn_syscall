#include "./header.h"

int global = 5;

int main() {
    pid_t pid;
    char* string = "I am parent";
    int local = 10;

    printf("before fork--- ");
    pid = fork();
    if (pid < 0) {
        err_exit("fork failed");
    }

    if (pid == 0) {
        string = "I am child";
        printf("%s, my pid = %d; global = %d; local = %d\n", \
                string, getpid(), global, local);
        global++;
    }
    else {
        printf("%s, my pid = %d; global = %d; local = %d\n", \
                string, getpid(), global, local);
        local++;
    }

    printf("At join point, %s; global = %d, local = %d\n", \
            string, global, local);

    exit(0);
}