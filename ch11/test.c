#include "./header.h"
#include "./header.c"

int main() {
    char str[256] = "hello, world\n";
    char* ptr = str;

    printf("%s\n%s\n", ptr, str);
    printf("%d %d\n", sizeof(str), sizeof(ptr));

    return 0;
}