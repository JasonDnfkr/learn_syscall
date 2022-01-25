#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    printf("hello world!\n");
    
    int a = 5;
    for (int i = 0; i < 10; i++) {
        printf("a = %d\n", a);
    }

    printf("input argument: %s\n", argv[1]);

    exit(EXIT_SUCCESS);
}