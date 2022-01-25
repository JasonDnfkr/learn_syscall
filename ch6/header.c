#include "./header.h"


#define err_exit(MESSAGE) (     \
    perror(MESSAGE),            \
    exit(1)                     \
)



void pr_exit(int status, pid_t pid) {
    int sig;
    if (WIFEXITED(status)) {
        printf("process %d normal termination, exit status = %d\n", pid, WEXITSTATUS(status));
    }
    else if (WIFSIGNALED(status)) {
        sig = WTERMSIG(status);
        printf("process %d abnormal termination, signal number = %d%s:\n", pid, sig, 
#ifdef WCOREDUMP
                WCOREDUMP(status) ? "(core file generated)" : "");
#else
                "");
#endif
        psignal(sig, "");
    }
    else if (WIFSTOPPED(status)) {
        sig = WSTOPSIG(status);
        printf("process %d stopped, signal number = %d: ", pid, sig);
        psignal(sig, "");
    }
}
