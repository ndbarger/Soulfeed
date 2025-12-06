#include <stdio.h>

#include "server.h"
#include "error.h"
#include "request.h"
#include "threading.h"

/*
TODO:

Logic needed for handling multiple clients.
*/

DWORD WINAPI server_handle_client(void* arg)
{
    SOCKET client_socket = (SOCKET)arg;
    char buffer[1024];
    int bytes;

    while ((bytes = recv(client_socket, buffer, sizeof(buffer), 0)) > 0)
    {
        buffer[bytes] = '\0';
        printf("Client %d: %s\n", client_socket, buffer);
        send(client_socket, buffer, bytes, 0);
    }

    closesocket(client_socket);

    return 0;
}

void server_cleanup(Server *s)
{
    closesocket(s->client_socket);
    closesocket(s->listen_socket);

    WSACleanup();
}

int server_initialize(Server *s)
{
    int result;

    s->running = TRUE;
    
    s->addr_len = sizeof(s->client_addr);

    // Winsock initialization
    result = WSAStartup(MAKEWORD(2, 2), &s->wsaData);
    if (result != 0)
    {
        error_throw(ERROR_WSA_STARTUP, result);
        return 1;
    }

    // Socket creation
    s->listen_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s->listen_socket == INVALID_SOCKET)
    {
        error_throw(ERROR_SOCKET_INIT, WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // Bind socket to IP/Port
    s->server_addr.sin_family = AF_INET;
    s->server_addr.sin_addr.s_addr = INADDR_ANY; // listen on all interfaces
    s->server_addr.sin_port = htons(SERVER_PORT);

    if (bind(s->listen_socket, (SA*)&s->server_addr, sizeof(s->server_addr)) == SOCKET_ERROR)
    {

        error_throw(ERROR_SERVER_BIND, WSAGetLastError());
        server_cleanup(s);
        return 1;
    }

    // Initialize clients

    printf("Server initialized.\n");

    return 0;
}

void server_run(Server *s)
{
    while (s->running)
    {
        s->client_socket = accept(s->listen_socket, NULL, NULL);

        Thread* t = thread_create(server_handle_client, (void*)s->client_socket);
        thread_close(t);
    }

    server_cleanup(s);
}