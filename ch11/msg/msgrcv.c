#include "../cs/csheader.h"
#include "../header.h"
#include "../header.c"
#include "./msgheader.h"

int main() {
    int running = 1;
    int msgid;
    struct my_msg msgbuf;

    if ((msgid = msgget((key_t)1234, 0666|IPC_CREAT)) == -1) {
        err_exit("msgget failed");
    }

    while (running) {
        if (msgrcv(msgid, (void*)&msgbuf, BUFSZ, -57, IPC_NOWAIT) != -1) {
            printf("You wrote: %s", msgbuf.text);
        }
        else if (errno == ENOMSG && msgrcv(msgid, (void*)&msgbuf, BUFSZ, 0, 0) != -1) {
            printf("You wrote: %s", msgbuf.text);
        }
        else {
            err_exit("msgrcv failed!\n");
        }

        if (strncmp(msgbuf.text, "end", 3) == 0) {
            break;
        }
    }

    if (msgctl(msgid, IPC_RMID, 0) == -1) {
        err_exit("msgctl(IPC_RMID) failed!\n");
    }

    exit(EXIT_SUCCESS);
}