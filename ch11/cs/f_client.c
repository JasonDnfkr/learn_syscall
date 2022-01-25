#include "./csheader.h"
#include "../header.h"
#include "../header.c"

int main() {
    struct data_to_pass data;
    int fd_server;
    int fd_client;
    int nbytes;
    char client_name[256];

    data.client_pid = getpid();
    sprintf(client_name, CLIENT_FIFO_NAME, data.client_pid);

    mkfifo(client_name, 0777);

    fd_server = open(SERVER_FIFO_NAME, O_WRONLY);
    if (fd_server < 0) {
        err_exit("cannot connect to server.\n");
    }

    while (1) {
        printf("enter your msg: ");
        char* msg = data.data;
        fgets(msg, sizeof(data.data), stdin);

        if (strcmp(msg, "BYE\n") == 0 || strcmp(msg, "bye\n") == 0) {
            printf("quit.\n");
            break;
        }

        int n = write(fd_server, &data, sizeof(data));
        if (n < 0) {
            err_exit("write to fifo failed!\n");
            exit(EXIT_FAILURE);
        }

        fd_client = open(client_name, O_RDONLY);
        if (fd_client < 0) {
            err_exit("msg received failed!\n");
        }

        n = read(fd_client, &data, sizeof(data));
        printf("back msg: %s\n", msg);  
        close(fd_client);
    }
    
    close(fd_server);
    unlink(CLIENT_FIFO_NAME);
    exit(EXIT_SUCCESS);
}