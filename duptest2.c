#include "./header.h"

int main() {
    int fd;
    fd = open("./output2", O_WRONLY|O_CREAT, 0644);
    if (fd == -1) {
        err_exit("OPEN FILE FAILED!");
        return -1;
    }
    
    if (dup2(fd, STDOUT_FILENO) == -1) {
        err_exit("dup2() failed!");
    }

    printf("20220120test for dup2()\n");
    return 0;
}