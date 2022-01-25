#include "./header.h"

int main() {
    printf("hello world!\n");

    int fd;
    if ((fd = open("output1", O_WRONLY|O_CREAT, 0644)) == -1) {
        err_exit("output1");
    }

    if (dup2(fd, STDOUT_FILENO) == -1) {
        err_exit("Redirect standard output failed");
    }
/*  */
    printf("this is a test program for redirect!\n");
    
    return 0;
}