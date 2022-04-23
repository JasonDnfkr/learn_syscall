#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long int uint64;

struct pair {
    int x;
    int y;
};

int main() {
    struct pair* p = (struct pair*)malloc(sizeof(struct pair));
    p->x = 55;
    p->y = 10;

    int* pp = (uint64)p;
    int* px = &p->x;
    int* py = &p->y; 

    printf("*pp = %d\n", *pp);
    printf("*px = %d,  *px = %d\n", *px, *py);
    printf("pp: %p, px: %p, py: %p\n", pp, px, py);
    printf("[%p]\n", (uint64)(pp + 1));

    // printf("%d\n", (int)(*p));

    struct pair** ptr = &p;

    printf("ptr_addr: %p\n", ptr);

    printf("%d %d\n", p->x, p->y);
    printf("%d %d\n", (*ptr)->x, (*ptr)->y);

    return 0;
}