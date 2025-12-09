#ifndef ERROR_H
#define ERROR_H

#define ERROR_WSA_MSG "Error initializing WSA: %d"
#define ERROR_SOCKET_MSG "Socket error: %d"
#define ERROR_SERVER_MSG "Server bind failed: %d"

#define ERROR_LEX_MSG "Undefined reference: %s"
#define ERROR_PARSE_MSG "Syntax error: %s"

/*
TODO: add built-in program closing after error; expand error handling functionality
*/

typedef enum
{
    ERROR_WSA_STARTUP,
    ERROR_SOCKET_INIT,
    ERROR_SERVER_BIND,
    ERROR_SOCKET_LISTEN
} ServerError;

typedef enum
{
    ERROR_LEX,
    ERROR_PARSE
} RequestError;

void s_error_throw(ServerError e, int code);
void l_error_throw(RequestError e, char* c);

#endif