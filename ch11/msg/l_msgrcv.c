#include "../cs/csheader.h"
#include "../header.h"
#include "../header.c"
#include "./msgheader.h"

void print_msg(const struct message* msgbuf) {
    printf("[Message received] %d\n", msgbuf->pid);
    printf("Time: %ld\n", msgbuf->time);
    printf("Content: %s\n", msgbuf->msg);
}

int main() {
    int msgid;
    struct message msgbuf;
    long int msg_type = -57;

    int msg_size = sizeof(msgbuf) - sizeof(msgbuf.msg_type);

    msgid = msgget((key_t)DEFAULT_KEY, IPC_CREAT|0666);
    if (msgid < 0) {
        err_exit("msgget failed");
    }

    while (1) {
        if (msgrcv(msgid, (void*)&msgbuf, msg_size, msg_type, IPC_NOWAIT) != -1) {
            print_msg(&msgbuf);
        }
        else if (errno == ENOMSG && msgrcv(msgid, (void*)&msgbuf, msg_size, 0, 0) != -1) {
            print_msg(&msgbuf);
        }
        else {
            err_exit("msgrcv failed!\n");
        }

        if (strncmp(msgbuf.msg, "close", 5) == 0) {
            break;
        }
    }
    if (msgctl(msgid, IPC_RMID, 0) == -1) {
        err_exit("msgctl(IPC_RMID) failed\n");
    }

    exit(EXIT_SUCCESS);
}