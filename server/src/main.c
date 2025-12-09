#include <stdio.h>

#include "server.h"
#include "lex.h"

int main()
{
    /*
    Server* server;

    if (server_initialize(server) == 1)
    {
        fprintf(stderr, "Error initializing server.\n");
        return 1;
    }

    server_run(server);
    */
   struct T_Lex* l = lex_code("hi there\n");

   printf("Done\n");

   printf("%s", l[1].value);

    return 0;
}