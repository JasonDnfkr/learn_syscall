#include "../cs/csheader.h"
#include "../header.h"
#include "../header.c"
#include "./msgheader.h"

void show_msq_stat(const struct msqid_ds* );

int main() {
    key_t key;
    int new;
    int msqid;
    int msgflg;
    struct msqid_ds buf;

    fprintf(stdout, "Enter the disired key = ");
    fscanf(stdin, "%d", &key);

    msgflg = S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP;
    if ((msqid = msgget(key, msgflg|IPC_CREAT|IPC_EXCL)) > 0) {
        new = 1;
    }
    else if (errno == EEXIST) {
        new = 0;
        msqid = msgget(key, msgflg);
    }
    else {
        err_exit("The msgget failed");
    }
    if (msgctl(msqid, IPC_STAT, &buf) == -1) {
        err_exit("msgctl failed");
    }

    show_msq_stat(&buf);
    if (new) {
        msgctl(msqid, IPC_RMID, NULL);
    }

    exit(EXIT_SUCCESS);
}

void show_msq_stat(const struct msqid_ds* buf) {
    printf("The USER ID = %d\n", buf->msg_perm.uid);
    printf("The Group ID = %d\n", buf->msg_perm.gid);
    printf("The CREATOR ID = %d\n", buf->msg_perm.cuid);
    printf("The CREATOR's GROUP ID = %d\n", buf->msg_perm.cgid);
    printf("The operation permissions = %#o", buf->msg_perm.mode);
    printf(" access permissions = %#o\n", buf->msg_perm.mode & 0777);
    printf("msg_cbytes = %ld\n", buf->__msg_cbytes);
    printf("msg_qbytes = %ld\n", buf->msg_qbytes);
    printf("msg_qnum = %ld\n", buf->msg_qnum);
    printf("msg_lspid = %d\n", buf->msg_lspid);
    printf("msg_lrpid = %d\n", buf->msg_lrpid);
    printf("msg_stime = %s", buf->msg_stime ? (char*)ctime(&(buf->msg_stime)) : "Not set\n");
    printf("msg_rtime = %s", buf->msg_rtime ? (char*)ctime(&(buf->msg_rtime)) : "Not set\n");
    printf("msg_ctime = %s", (char*)ctime(&(buf->msg_ctime)));
}