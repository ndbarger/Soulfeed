#include "request.h"

int current_request = 0;

void request_enqueue(Server *s, SOCKET sock, char* msg, int bytes)
{

}

int request_has_response(Server *s, SOCKET sock)
{
    return 0;
}

char* request_get_response(Server *s, SOCKET sock)
{
    return "Hello, world";
}