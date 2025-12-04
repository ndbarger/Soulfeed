#ifndef REQUEST_H
#define REQUEST_H

#include "server.h"

/*
Logic for requests
*/

void request_enqueue(Server *s, SOCKET sock, char* msg, int bytes);

int request_has_response(Server *s, SOCKET sock);
char* request_get_response(Server *s, SOCKET sock);

#endif