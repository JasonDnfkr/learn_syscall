#include "./header.h"
#include "./header.c"

int main() {
    char string[128];
    pid_t pid;
    int conn[2];
    char* filename = "output.txt";

    memset(string, 0, sizeof(string));

    if (pipe(conn) < 0) {
        err_exit("pipe failed!\n");
    }

    pid = fork();
    if (pid < 0) {
        err_exit("fork() failed!\n");
    }
    else if (pid == 0) {
        // sleep(2);
        close(STDIN_FILENO);
        dup2(conn[0], STDIN_FILENO);
        close(conn[0]);
        fgets(string, sizeof(string), stdin);
        // printf("%s", string);

        int conn_2[2];
        if (pipe(conn_2) < 0) {
            err_exit("pipe_2 failed!\n");
        }

        pid = fork();
        if (pid < 0) {
            err_exit("fork() for child failed!\n");
        }
        else if (pid == 0) {
            close(conn_2[1]);
            int n = read(conn_2[0], string, sizeof(string));
            if (n < 0) {
                err_exit("read failed!\n");
            }

            printf("[%s]\n", string);
            int file = open(filename, O_CREAT|O_WRONLY, 0644);
            write(file, string, sizeof(string));

            exit(EXIT_SUCCESS);
        }
        else {
            close(conn_2[0]);
            int n = write(conn_2[1], string, sizeof(string));
            if (n < 0) {
                err_exit("write failed!\n");
            }
        }

        exit(EXIT_SUCCESS);
    }
    else {
        fgets(string, sizeof(string), stdin);
        printf("fgets result: %s\n", string);

        int tmp = open("ck1.txt", O_CREAT|O_WRONLY, 0644);
        if (tmp < 0) {
            err_exit("test write failed!\n");
        }
        write(tmp, string, sizeof(string) - 1);

        close(STDIN_FILENO);
        dup2(conn[1], STDOUT_FILENO);
        close(conn[1]);
        printf("WRITING RESULT: %s\n", string);

        
 
        exit(EXIT_SUCCESS);
    }
}