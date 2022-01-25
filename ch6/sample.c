#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    printf("argument list: \n");
    for (int i = 0; i < argc; i++) {
        printf("[%d] %s\n", i + 1, argv[i]);
    }

    printf("hello world for sample 1\n");
    exit(EXIT_SUCCESS);
}