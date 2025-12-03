#include <stdio.h>

#include "server.h"
#include "error.h"

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

    // initialize master set
    FD_ZERO(&s->master_set);
    FD_SET(s->listen_socket, &s->master_set);

    printf("Server initialized.\n");

    return 0;
}

void server_run(Server *s)
{
    while (s->running)
    {
        s->read_set = s->master_set;
        s->write_set = s->master_set;

        if (select(0, &s->read_set, &s->write_set, NULL, NULL) == SOCKET_ERROR)
            break;
        
        for (int i = 0; i < MAX_CLIENTS; i++)
        {
            SOCKET s_ = i;
            
            if (FD_ISSET(s->listen_socket, &s->read_set))
            {
                s->client_socket = accept(s->listen_socket, (SA*)&s->client_addr, &s->addr_len);
                printf("New connection: %d\n", s->client_socket);
                FD_SET(s->client_socket, &s->master_set);
            } else if (FD_ISSET(s_, &s->read_set))
            {
                char buffer[BUFFER_SIZE];
                int bytes = recv(s_, buffer, sizeof(buffer), 0);

                if (bytes <= 0)
                {
                    printf("Client %d disconnected.\n", s_);
                    closesocket(s_);
                    FD_CLR(s_, &s->master_set);
                } else
                {
                    // insert request stuff
                    /*
                    request_enqueue(s_, buffer, bytes);
                    */
                    printf("Client %d: %s\n", s_, buffer);
                }
            } else if (FD_ISSET(s_, &s->write_set))
            {
                // insert request stuff
                /*
                if (request_has_response(s_))
                {
                    char* response = request_get_response(s_);
                    send(s, response, strlen(response), 0);
                }
                */
            }
        }
    }

    server_cleanup(s);
}