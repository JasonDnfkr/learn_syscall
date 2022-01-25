#include <sys/msg.h>
#include <errno.h>
#include <time.h>

#define BUFSZ 1024

struct my_msg {
    long int my_msg_type;
    char text[BUFSZ];
};
