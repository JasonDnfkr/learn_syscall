#include "./header.h"
#include "./header.c"

const char* file = "./ls.txt";
const char* fifo_file = "testfifo";

int main() {
    char buf[BUFSIZ];
    int fd;
    int fd_fifo;
    int n;

    fd = open(file, O_RDONLY);
    if (fd < 0) {
        err_exit("open input file failed!\n");
    }

    memset(buf, 0, sizeof(buf));

    while ((n = read(fd, buf, sizeof(buf))) != 0) {}
    close(fd);

    fd_fifo = open(fifo_file, O_WRONLY);
    if (fd_fifo < 0) {
        err_exit("open fifo file failed!\n");
    }

    // printf("%ld\n", strlen(buf));
    // int tmp = open("testfile", O_WRONLY|O_CREAT, 0644);

    // write(tmp, buf, sizeof(buf));
    write(fd_fifo, buf, strlen(buf) + 1);
    close(fd_fifo);

    exit(EXIT_SUCCESS);
}