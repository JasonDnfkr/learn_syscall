#include "./header.h"
#include "./header.c"

void parse(char* buf, char* args[]) {
    int i = 0;
    while (*buf != '\0') {
        args[i] = buf;
        i++;
        while ((*buf != ' ') && (*buf != '\t') && (*buf != '\n')) buf++;
        while ((*buf == ' ') || (*buf == '\t' || (*buf == '\n'))) {
            *buf = '\0';
            buf++;
        }
    }
    args[i] = '\0';
}

void execute(char* args[]) {
    pid_t pid;
    int status;
    pid = fork();
    if (pid < 0) {
        err_exit("fork");
    }
    else if (pid == 0) {
        execvp(args[0], args);
        err_exit("execvp");
    }

    waitpid(pid, &status, 0);
    pr_exit(status, pid);
}


int main() {
    char buf[1024];
    char* args[64];
    char* cp;
    while (1) {
        printf("Command: ");
        cp = fgets(buf, sizeof(buf), stdin);
        if (cp == (char*)NULL || *cp == '\n') {
            printf("quit\n");
            exit(EXIT_SUCCESS);
        }

        parse(buf, args);
        execute(args);
    }

    exit(EXIT_SUCCESS);
}