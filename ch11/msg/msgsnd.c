#include "../cs/csheader.h"
#include "../header.h"
#include "../header.c"
#include "./msgheader.h"

void show_msg_stat(int msqid) {
    struct msqid_ds buf;
    if (msgctl(msqid, IPC_STAT, &buf) == -1) {
        err_exit("msgctl() failed");
    }
    printf("msg_qbytes = %ld\n", buf.msg_qbytes);
}

int main() {
    int msgid = 1;
    int running = 1;
    struct my_msg msgbuf;
    struct msqid_ds buf;


    msgid = msgget((key_t)1234, 0666|IPC_CREAT);
    if (msgid == -1) {
        err_exit("msgget failed\n");
    }

    show_msg_stat(msgid);

    while (running) {
        printf("Enter some text: ");
        fgets(msgbuf.text, BUFSZ, stdin);
        msgbuf.my_msg_type = (long int)msgbuf.text[0];
        // printf("entered: %s\n", msgbuf.text);
        if (msgsnd(msgid, (void*)&msgbuf, sizeof(msgbuf.text), IPC_NOWAIT) == -1) {
            err_exit("msgsnd failed\n");
        }
        if (strncmp(msgbuf.text, "end", 3) == 0) {
            running = 0;
        }
    }
   
    exit(EXIT_SUCCESS);
}