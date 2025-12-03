#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <winsock2.h>
#include <ws2tcpip.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8080
#define BUFFER_SIZE 1024

WSADATA wsaData;
SOCKET client_socket = INVALID_SOCKET;
struct sockaddr_in server_addr;
char buffer[BUFFER_SIZE];
int result;

void client_cleanup()
{
    closesocket(client_socket);
    WSACleanup();
}

int client_initialize()
{
    result = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (result != 0)
    {
        fprintf(stderr, "WSAStartup failed: %d\n", result);
        return 1;
    }

    client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (client_socket == INVALID_SOCKET)
    {
        fprintf(stderr, "Socket creation failed: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0)
    {
        fprintf(stderr, "Invalid address/Address not supported.\n");
        client_cleanup();
        return 1;
    }

    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR)
    {
        fprintf(stderr, "Connection failed: %d\n", WSAGetLastError());
        client_cleanup();
        return 1;
    }
    printf("Connected to server %s:%d\n", SERVER_IP, SERVER_PORT);
}

int main()
{
    if (client_initialize() == 1)
        return 1;

    const char *message = "Hello from the client!";
    result = send(client_socket, message, (int)strlen(message), 0);
    if (result == SOCKET_ERROR)
    {
        fprintf(stderr, "Send failed: %d\n", WSAGetLastError());
        client_cleanup();
        return 1;
    }
    printf("Sent: %s\n", message);

    result = recv(client_socket, buffer, BUFFER_SIZE-1, 0);
    if (result > 0)
    {
        buffer[result] = '\0';
        printf("Recieved: %s\n", buffer);
    } else if (result == 0)
    {
        printf("Connection closed by server.\n");
    } else
    {
        printf("Recv fauled: %d\n", WSAGetLastError());
    }

    client_cleanup();
    
    return 0;
}