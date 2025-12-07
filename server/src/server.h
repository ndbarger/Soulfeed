#ifndef SERVER_H
#define SERVER_H

#include <winsock2.h>
#include <ws2tcpip.h>

#define SA struct sockaddr

#define SERVER_PORT 8080
#define BUFFER_SIZE 1024
#define MAX_CLIENTS 32

typedef struct Server
{
    /* server object */
    WSADATA wsaData;
    SOCKET listen_socket;
    struct sockaddr_in server_addr, client_addr;
    SOCKET clients[MAX_CLIENTS];
    int addr_len;
    int running;
} Server;

DWORD WINAPI server_handle_client(void* arg);

int server_initialize(Server *s);
void server_run(Server *s);

#endif