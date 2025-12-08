#ifndef REQUEST_H
#define REQUEST_H

#include "server.h"
#include "lex.h"

/*
Logic for requests
*/

typedef struct
{
    SOCKET socket;
    char* msg;
    LexToken func;
} Request;


void request_enqueue(Server *s, SOCKET sock, char* msg, int bytes);

int request_has_response(Server *s, SOCKET sock);
char* request_get_response(Server *s, SOCKET sock);

#endif