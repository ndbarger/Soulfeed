#include <stdio.h>

#include "error.h"

void s_error_throw(ServerError e, int code)
{
    char* msg;

    if (e == ERROR_WSA_STARTUP)
    {
        msg = ERROR_WSA_MSG;
    } else if (e == ERROR_SOCKET_INIT)
    {
        msg = ERROR_SOCKET_MSG;
    } else if (e == ERROR_SERVER_BIND)
    {
        msg = ERROR_SERVER_MSG;
    } else if (e == ERROR_SOCKET_LISTEN)
    {
        msg = ERROR_SOCKET_MSG;
    }

    fprintf(stderr, "%s", msg, code);
}

void l_error_throw(RequestError e, char* c)
{
    char* msg;

    if (e == ERROR_LEX)
    {
        msg = ERROR_LEX_MSG;
    } else if (e == ERROR_PARSE)
    {
        msg = ERROR_PARSE_MSG;
    }

    fprintf(stderr, "%s", msg, c);
}