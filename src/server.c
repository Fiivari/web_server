#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include "../include/server.h"

int main() {

    int sockfd = create_and_bind_socket();
    if (sockfd == -1) {
        printf("Failed to create and bind socket\n");
        return 1;
    }

    if (listen(sockfd, SOMAXCONN) == SOCKET_ERROR) {
        printf("Listen failed with error: %d\n", WSAGetLastError());
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    handle_connections(sockfd);

    closesocket(sockfd);
    WSACleanup();

    return 0;
}
