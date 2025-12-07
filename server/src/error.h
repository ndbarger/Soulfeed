#ifndef ERROR_H
#define ERROR_H

#define ERROR_WSA_MSG "Error initializing WSA: %d"
#define ERROR_SOCKET_MSG "Socket error: %d"
#define ERROR_SERVER_MSG "Server bind failed: %d"

typedef enum ServerError
{
    ERROR_WSA_STARTUP,
    ERROR_SOCKET_INIT,
    ERROR_SERVER_BIND,
    ERROR_SOCKET_LISTEN
} ServerError;

void error_throw(ServerError e, int code);

#endif