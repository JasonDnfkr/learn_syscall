#include "./ch13.h"
#include <unistd.h>
#define SIZE 30000
#define BLOCK 5000

int arr[SIZE];
int check[SIZE / 50];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void fun(int* arg) {
    int begin = arg[0];
    int end = arg[1];
    printf("begin: %d  end: %d\n", begin, end);


    int index = begin;
    while (index < end) {
        int point = index / BLOCK;
        pthread_mutex_lock(&mutex);
        if (check[point] == 0) {
            index = (point + 1) * BLOCK > end ? end : (point + 1) * BLOCK;
            for (int i = point * BLOCK; i < index; i++) {
                arr[i] += rand() % 10000;
            }
            check[point] = 1;
        }
        else {
            index += BLOCK;
        }
        pthread_mutex_unlock(&mutex);
        printf("point: %d,  index: %d\n", point, index);
    }

    pthread_exit(NULL);
}


int main() {
    pthread_t tid1;
    pthread_t tid2;
    int rv;

    // int a[2] = { 0, SIZE / 2 };
    // int b[2] = { SIZE / 2, SIZE };    
    
    int a[2] = { 0, SIZE };
    int b[2] = { 0, SIZE };
    
    rv = pthread_create(&tid1, NULL, (void* (*)(void*))fun, (void*)a);
    check_error(rv, "pthread_create: tid1\n");

    rv = pthread_create(&tid2, NULL, (void* (*)(void*))fun, (void*)b);
    check_error(rv, "pthread_create: tid1\n");

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    for (int i = 0; i < SIZE; i += 5) {
        printf("%7d %7d %7d %7d %7d\n", arr[i], arr[i+1], arr[i+2], arr[i+3], arr[i+4]);
    }

    exit(0);
}