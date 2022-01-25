#include "./header.h"
#include "./header.c"

const char* fifo_file = "testfifo";

int main() {
    int fd_fifo;
    char buf[BUFSIZ];

    if (access(fifo_file, F_OK) == -1) {
        if (mkfifo(fifo_file, 0644) != 0) {
            printf("Could not create fifo %s\n", fifo_file);
            exit(EXIT_FAILURE);
        }
    }

    fd_fifo = open(fifo_file, O_RDONLY);
    if (fd_fifo < 0) {
        err_exit("Could not open fifo file");
    }

    read(fd_fifo, buf, BUFSIZ);
    close(fd_fifo);

    printf("%s", buf);

    exit(EXIT_SUCCESS);
}