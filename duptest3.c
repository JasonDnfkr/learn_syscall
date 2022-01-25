#include "./header.h"

int main() {
    int fd;
    const int BUF_SIZE = 1024;

    fd = open("./input2.txt", O_RDWR);
    if (fd == -1) {
        err_exit("open file failed!");
    }

    dup2(fd, STDIN_FILENO);

    char str[BUF_SIZE];

    scanf("%[^\n]", str);
    printf("result:\n%s\n", str);

    return 0;
}