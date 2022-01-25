#include "./header.h"
#include "./header.c"

void parse(char* buf, char* args[]) {
    int i = 0;
    while (*buf != '\0') {
        args[i] = buf;
        i++;
        while ((*buf != ' ') && (*buf != '\t') && (*buf != '\n')) {
            buf++;
        }
        while ((*buf == ' ') || (*buf == '\t') || (*buf == '\n')) {
            *buf = '\0';
            buf++;
        }
    }
    args[i] = NULL;
}

void execute(char* args[]) {
    pid_t pid;
    int status;

    pid = fork();
    if (pid < 0) {
        perror("fork");
    }
    else if (pid == 0) {
        execvp(args[0], args);
        perror("execvp");
    }
    else {
        waitpid(pid, &status, 0);
        pr_exit(status, pid);
    }
}

int main() {
    char buf[128];
    char* args[64];

    while (1) {
        printf("Command: ");
        fgets(buf, sizeof(buf), stdin);

        if (buf[0] == ' ' || buf[0] == '\t' || buf[0] == '\n') {
            printf("quit\n");
            exit(EXIT_SUCCESS);
        }
        // printf("%s\n", buf);

        parse(buf, args);
        execute(args);

        // int i = 0;
        // while (args[i] != NULL) {
        //     printf("%s\n", args[i]);
        //     i++;
        // }
    }

    exit(EXIT_SUCCESS);
}