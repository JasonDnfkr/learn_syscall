#include "./ch13.h"

typedef unsigned long long int uint64;

int a[2] = { 49, 5 };
int b[2] = { 66, 77 };

struct pair {
    int x;
    int y;
};

void thread_run(int* arg) {
    int* ap = arg;
    struct pair* res = (struct pair*)malloc(sizeof(struct pair));
    res->x = ap[0];
    res->y = ap[1];

    printf("addr in function: %p\n", (uint64)res);

    pthread_exit((void*)res);
}

int main() {
    pthread_t tid1, tid2;
    int rv;
    struct pair** ptr1;
    struct pair** ptr2;


    rv = pthread_create(&tid1, NULL, (void*(*)())thread_run, a);
    check_error(rv, "pthread_create: tid1\n");

    rv = pthread_create(&tid2, NULL, (void*(*)())thread_run, b);
    check_error(rv, "pthread_create: tid2\n");

    pthread_join(tid1, (void**)&ptr1);
    pthread_join(tid2, (void**)&ptr2);

    printf("end\n");

    printf("&ptr1 addr: %p\n", (uint64)&ptr1);
    printf("ptr1 addr: %p\n", (uint64)ptr1);
    printf("*ptr1 addr: %p\n", (uint64)*ptr1);
    // printf("**ptr1 addr: %p\n", (uint64)**ptr1);

    struct pair* ans1 = (struct pair*)ptr1;
    struct pair* ans2 = (struct pair*)ptr2;

    // int ans1_x = (struct )ptr1;
    // int ans1_y = (int)*(ptr1 + 1);

    printf("ans1_x: %d, ans1_y: %d\n", ans1->x, ans1->y);
    printf("ans2_x: %d, ans2_y: %d\n", ans2->x, ans2->y);


    // printf("thread 1: %d\nthread 2: %d\n", *ptr1, *ptr2);

    exit(0);
}