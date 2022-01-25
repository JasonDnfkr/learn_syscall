#include <sys/msg.h>
#include <errno.h>
#include <time.h>

#define BUFSZ 1024
#define DEFAULT_KEY 1234

struct my_msg {
    long int my_msg_type;
    char text[BUFSZ];
};

struct message {
    long int msg_type;
    pid_t pid;
    long int time;
    char msg[BUFSZ];
};