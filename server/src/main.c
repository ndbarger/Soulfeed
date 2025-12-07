#include <stdio.h>

#include "server.h"

int main()
{
    Server* server;

    if (server_initialize(server) == 1)
    {
        fprintf(stderr, "Error initializing server.\n");
        return 1;
    }

    server_run(server);

    return 0;
}