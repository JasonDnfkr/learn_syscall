#include "./header.h"
#include "./header.c"

void read_data(FILE* stream) {
    char buf[BUFSIZ];
    // fgets(buf, sizeof(buf), stream);
    fread(buf, 32, sizeof(buf) / 32, stream);
    fprintf(stdout, "%s", buf);
}

int main() {
    FILE* input;
    input = popen("ls -l", "r");
    if (!input) {
        err_exit("popen failed");
    }
    read_data(input);
    pclose(input);
    return EXIT_SUCCESS;
}