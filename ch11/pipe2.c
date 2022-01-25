#include "./header.h"
#include "./header.c"

int main() {
    pid_t pid;
    int fd[2];
    int len;
    char buffer[BUFSIZ];

    if (pipe(fd) != 0) {
        err_exit("pipe creation failed");
    }

    if ((pid = fork()) == 0) {
        printf("now: child process\n");
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);

        printf("now executing cat: ");
        if (execl("/bin/cat", "cat", NULL, NULL) == -1) {
            err_exit("Unable to run cat");
        }
    }
    else {
        printf("now: parent process\n");
        close(fd[0]);
        printf("you can type a line and the line will echoed: \n");
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);

        while (gets(buffer) != NULL) {
            printf("entered\n");
            puts(buffer);
        }
    }



    return 0;
}