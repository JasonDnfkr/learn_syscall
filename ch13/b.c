#include "./ch13.h"
#define SIZE 10
#define HUGE 44000

int a[SIZE];
int b[HUGE];

void max_fun(int* arg) {
    int* ap = arg;
    int  rv;
    int k = 0;
    for (int i = 1; i < SIZE; i++) {
        if (ap[i] > ap[k]) k = i;
    }
    int* new = (int*)malloc(sizeof(int));
    *new = ap[k];
    printf("new = %d\n", *new);
    pthread_exit((void*)new);
}

void max_fun2(int* arg) {
    int* ap = arg;
    int  rv;
    int k = 0;
    for (int i = 1; i < HUGE; i++) {
        if (ap[i] > ap[k]) k = i;
    }
    int* new = (int*)malloc(sizeof(int));
    *new = ap[k];
    printf("new = %d\n", *new);
    pthread_exit((void*)new);
}

int main() {
    pthread_t tid1, tid2;
    int rv;
    int** ptr1;
    int** ptr2;
    for (int i = 1; i < SIZE; i++) {
        a[i] = rand();
    }
    for (int i = 1; i < HUGE; i++) {
        b[i] = rand();
    }

    rv = pthread_create(&tid2, NULL, max_fun2, b);
    check_error(rv, "pthread_create: tid2");
    rv = pthread_create(&tid1, NULL, max_fun, a);
    check_error(rv, "pthread_create: tid1");

    pthread_join(tid2, &ptr2);
    pthread_join(tid1, &ptr1);


    printf("thread1's max value is: %d\n", *ptr1);
    printf("thread2's max value is: %d\n", *ptr2);
    printf("max value = %d\n", (*ptr1) > (*ptr2) ? (*ptr1) : (*ptr2));

    exit(0);
}

