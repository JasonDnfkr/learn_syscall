#include "./header.h"
#include "./header.c"

int main() {
    pid_t pid;
    int n;
    int mypipe[2];

    char buffer[BUFSIZ + 1];
    char some_data[] = "hello world!";

    if (pipe(mypipe)) {
        err_exit("pipe failed.\n");
    }

    if ((pid = fork()) < 0) {
        err_exit("fork failed.\n");
    }

    if (pid == 0) {
        close(mypipe[1]);
        n = read(mypipe[0], buffer, BUFSIZ);
        printf("child %d: read %d bytes: %s\n", getpid(), n , buffer);
    }
    else {
        close(mypipe[0]);
        n = write(mypipe[1], some_data, strlen(some_data));
        printf("parent %d: write %d bytes: %s\n", getpid(), n, some_data);
    }

    exit(EXIT_SUCCESS);
}