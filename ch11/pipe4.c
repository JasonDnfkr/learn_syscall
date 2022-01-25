#include "./header.h"
#include "./header.c"

void write_data(FILE* stream) {
    for (int i = 0; i < 50; i++) {
        fprintf(stream, "line %2d\n", i);
        if (ferror(stream)) {
            err_exit("output to stream failed.\n");
        }
    }
}

int main() {
    FILE* output;
    output = popen("more -10", "w");
    if (!output) {
        err_exit("Could not run more. \n");
    }
    write_data(output);
    pclose(output);

    return EXIT_SUCCESS;
}