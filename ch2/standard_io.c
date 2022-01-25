#include "./header.h"
#include "../header.h"

int main() {
    FILE* stream;

    char buf[80];
    printf("open and create test_file\n");
    stream = fopen("test_file", "w");
    if (stream == NULL) {
        err_exit("fopen() failed");
    }

    printf("write string to test_file\n");
    fputs("hello world!", stream);

    stream = freopen("test_file", "r", stream);
    if (stream == NULL) {
        err_exit("freopen() failed");
    }
    printf("reading string from test_file\n");
    fgets(buf, sizeof(buf), stream);
    printf("the string is \"%s\"\n", buf);

    fclose(stream);

    return 0;
}