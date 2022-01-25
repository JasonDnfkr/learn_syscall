#include "./header.h"
// #include <stdio.h>

// #define TEST 55

int main() {
    int a = 10;
#ifdef TEST
    a++;
    printf("a = %d, TEST = %d\n", a, TEST);
#else
    a--;
    printf("a = %d\n", a);
#endif
    return 0;
}