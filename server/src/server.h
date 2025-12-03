#ifndef SERVER_H
#define SERVER_H

#include <winsock2.h>
#include <ws2tcpip.h>

#define SA struct sockaddr

#define SERVER_PORT 8080
#define BUFFER_SIZE 1024
#define MAX_CLIENTS FD_SETSIZE

typedef struct Server
{
    /* server object */
    WSADATA wsaData;
    SOCKET listen_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    fd_set master_set, read_set, write_set;
    int addr_len;
    int running;
} Server;

int server_initialize(Server *s);
void server_run(Server *s);

#endif