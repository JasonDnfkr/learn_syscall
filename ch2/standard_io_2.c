#include "./header.h"
#include "../header.h"

// const int BUFSIZ = 512;

int main(int argc, char** argv) {
    int n;
    FILE* from;
    FILE* to;
    char buf[BUFSIZ];

    if (argc != 3) {
        fprintf(stderr, "Usage: %s from-file to-file\n", *argv);
        exit(EXIT_FAILURE);
    }

    from = fopen(argv[1], "r");
    if (from == NULL) {
        err_exit(argv[1]);
    }

    to = fopen(argv[2], "a");
    if (to == NULL) {
        err_exit(argv[2]);
    }

    // while ((n = fread(buf, sizeof(char), BUFSIZ, from)) > 0) {
    //     fwrite(buf, sizeof(char), n, to);
    // }

    while ((n = fread(buf, 4, BUFSIZ / 4, from)) > 0) {
        fwrite(buf, 8, n / 8, to);
    }

    fclose(from);
    fclose(to);
    exit(EXIT_SUCCESS);
}