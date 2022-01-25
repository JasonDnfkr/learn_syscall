#include "../cs/csheader.h"
#include "../header.h"
#include "../header.c"
#include "./msgheader.h"

int main() {
    int msgid;
    struct message msgbuf;
    struct msqid_ds buf;

    int msg_size = sizeof(msgbuf) - sizeof(msgbuf.msg_type);

    msgid = msgget((key_t)DEFAULT_KEY, IPC_CREAT|0666);
    if (msgid == -1) {
        err_exit("msgget() failed\n");
    }

    while (1) {
        printf("Enter the message: ");
        fgets(msgbuf.msg, sizeof(msgbuf.msg), stdin);
        msgbuf.msg_type = (long int)msgbuf.msg[0];
        msgbuf.pid = getpid();
        msgbuf.time = time(NULL);

        if (msgsnd(msgid, (void*)&msgbuf, msg_size, IPC_NOWAIT) == -1) {
            err_exit("msgsnd failed\n");
        }

        if (strncmp(msgbuf.msg, "close", 5) == 0) {
            break;
        }
    }

    exit(EXIT_SUCCESS);
}