#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>

/*
void err_exit(const char* msg) {
    printf("output\n");
}
*/

#define err_exit(MESSAGE) (     \
    perror(MESSAGE),            \
    exit(1)                     \
)

