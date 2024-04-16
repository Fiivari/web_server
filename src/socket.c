#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include "../include/socket.h"

#define BUFFER_SIZE 1024

int create_and_bind_socket() {
    WSADATA wsaData;
    int sockfd;
    struct sockaddr_in servaddr;

    // Initialize Winsock and store the information in wsaData
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        printf("WSAStartup failed with error: %d\n", WSAGetLastError());
        return -1;
    }

    // Creating socket file descriptor using the Winsock API
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Socket creation failed with error: %d\n", WSAGetLastError());
        WSACleanup();
        return -1;
    }

    servaddr.sin_family = AF_INET;                         // IPv4 protocol
    servaddr.sin_port = htons(9999);                       // Port number
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");     // Set IP to localhost

    // Bind the socket with the server address
    // servaddr is converted to sockaddr type
    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == SOCKET_ERROR) {
        printf("Bind failed with error: %d\n", WSAGetLastError());
        closesocket(sockfd);
        WSACleanup();
        return -1;
    }

    return sockfd;
}