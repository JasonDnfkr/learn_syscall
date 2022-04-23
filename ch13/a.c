#include "./ch13.h"
#define NUM_THREADS 4

struct pair {
    int x;
    int y;
};

void pthread_test(void* t) {
    pthread_t my_tid;
    my_tid = pthread_self();
    printf("\tThread %d: my tid is %lx, Hello World!\n", t, my_tid);
}

int fun(int a) {
    int b = a + 4;
    return b;
}

int fun2(int a, int b) {
    return a + b;
}

void testfun(int (*fun)(int), int a) {
    printf("testfun: %d\n", fun(a));
}

void testfun2(int(*fun)(int, int), struct pair* p) {
    int x = p->x;
    int y = p->y;
    printf("testfun2: %d\n", fun(x, y));
}

char* fun3(struct pair* p) {
    char* str = (char*)malloc(sizeof(char) * 10);
    str[0] = p->x + '0';
    str[1] = '|';
    str[2] = '|';
    str[3] = p->y + '0';
    str[4] = '\0';

    return str;
}

void testfun3(char* (*fun)(struct pair*), struct pair* p) {
    char* ss = fun3(p);
    printf("testfun3: %s\n", ss);
}

int main() {
    pthread_t tid;
    int rv;
    for (int t = 0; t < NUM_THREADS; t++) {
        rv = pthread_create(&tid, NULL, (void *(*)(void*))pthread_test, (void*)t);
        printf("created thread %lx\n", tid);
    }
    printf("Goodbye\n");
    testfun((int (*)(int))fun, 66);

    struct pair p;
    // p = (struct pair*)malloc(sizeof(struct pair));
    p.x = 3;
    p.y = 6;

    testfun2((int (*)(int,int))fun2, &p);

    testfun3((char* (*)(struct pair*))fun3, &p);

    pthread_exit(NULL);
}