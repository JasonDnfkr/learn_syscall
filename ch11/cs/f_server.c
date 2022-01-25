#include "./csheader.h"
#include "../header.h"
#include "../header.c"

int main() {
    struct data_to_pass data;
    int fd_server;
    int fd_client;
    char* ptr;
    int nbytes;
    char client_name[256];


    mkfifo(SERVER_FIFO_NAME, 0777);
    fd_server = open(SERVER_FIFO_NAME, O_RDONLY);
    if (fd_server < 0) {
        err_exit("server fifo failure");
    }

    do {
        nbytes = read(fd_server, &data, sizeof(data));
        printf("Received data from pid %d, msg: %s\n", data.client_pid, data.data);
        if (nbytes < 0) {
            err_exit("nbytes read failed!\n");
            break;
        }
        if (nbytes == 0) {
            printf("All connection disconnected. Reopening the fifo file..\n");
            close(fd_server);
            unlink(SERVER_FIFO_NAME);

            mkfifo(SERVER_FIFO_NAME, 0777);
            fd_server = open(SERVER_FIFO_NAME, O_RDONLY);
            nbytes = read(fd_server, &data, sizeof(data));
            printf("Received data from pid %d, msg: %s\n", data.client_pid, data.data);
            if (nbytes < 0) {
               err_exit("nbytes read failed!\n");
              break;
            }
        }
        ptr = data.data;
        while (*ptr != '\0') {
            if (isupper(*ptr)) {
                *ptr = tolower(*ptr);
            }
            else if (islower(*ptr)) {
                *ptr = toupper(*ptr);
            }
            ptr++;
        }

        sprintf(client_name, CLIENT_FIFO_NAME, data.client_pid);
        // printf("client name: %s\n", client_name);
        fd_client = open(client_name, O_WRONLY);
        if (fd_client < 0) {
            err_exit("client open failed");
        }
        int n = write(fd_client, &data, sizeof(data));
        if (n < 0) {
            err_exit("write to client failed");
        }
        close(fd_client);
    } while (nbytes > 0);

    // do {
    //     nbytes = read(fd_server, &data, sizeof(data));
    //     fprintf(stdout, "data received: %s\n", data.data);
    //     if (nbytes > 0) {
    //         ptr = data.data;
    //         while (*ptr != '\0') {
    //             if (isupper(*ptr)) {
    //                 *ptr = tolower(*ptr);
    //             }
    //             else if (islower(*ptr)) {
    //                 *ptr = toupper(*ptr);
    //             }
    //             ptr++;
    //         }

    //         sprintf(client_name, CLIENT_FIFO_NAME, data.client_pid);
    //         fd_client = open(client_name, O_WRONLY);
    //         if (fd_client != -1) {
    //             write(fd_client, &data, sizeof(data));
    //             close(fd_client);
    //         }
    //     }
    // } while (nbytes > 0);    

    close(fd_server);
    unlink(SERVER_FIFO_NAME);

    exit(EXIT_SUCCESS);
}