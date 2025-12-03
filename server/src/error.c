#include <stdio.h>

#include "error.h"

void error_throw(ServerError e, int code)
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
    }

    fprintf(stderr, "%s", msg, code);
}