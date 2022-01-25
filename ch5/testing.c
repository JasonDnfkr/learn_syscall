#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    printf("original program..\n");

    int exe = execlp("./prog", "prog", "test arg", (char*)(0));
    if (exe < 0) {
        printf("execlp error\n");
        exit(EXIT_FAILURE);
    }

    printf("will this show?");

    exit(EXIT_SUCCESS);
}