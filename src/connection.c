#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include "../include/connection.h"

#define BUFFER_SIZE 1024

void handle_connections(int sockfd) {
    struct sockaddr_in cliaddr;
    int clilen = sizeof(cliaddr);
    SOCKET newsockfd;

    // Accept incoming connections and handle them
    while ((newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, &clilen)) != INVALID_SOCKET) {
        char buffer[BUFFER_SIZE];
        int bytes_received;
        int header_end = 0; 

        // Receive data from the client
        while (!header_end && (bytes_received = recv(newsockfd, buffer, BUFFER_SIZE, 0)) > 0) {
            printf("%.*s", bytes_received, buffer);

            for (int i = 0; i < bytes_received - 1; i++) {
                if (buffer[i] == '\r' && buffer[i + 1] == '\n') {
                    header_end = 1;
                    break;
                }
            }
        }

        if (bytes_received == SOCKET_ERROR) {
            printf("Receive failed with error: %d\n", WSAGetLastError());
            closesocket(newsockfd);
            continue;
        }

        // Parse the request line to extract the requested resource
        char method[10], resource[100], protocol[20];
        sscanf(buffer, "%s %s %s", method, resource, protocol);

        // Check if the request method is GET and the requested resource is valid
        if (strcmp(method, "GET") == 0 && strcmp(resource, "/") == 0) {
            // Send index.html file
            send_file(newsockfd, "index.html");
        } else {
            // Send 404 Not Found response for unsupported methods or invalid resources
            const char *response = "HTTP/1.1 404 Not Found\r\n\r\n";
            send(newsockfd, response, strlen(response), 0);
        }

        closesocket(newsockfd);
    }
}

void send_file(SOCKET sockfd, const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("Failed to open file: %s\n", filename);
        return;
    }

    char buffer[BUFFER_SIZE];
    size_t bytes_read;

    // Send HTTP header
    const char *header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
    send(sockfd, header, strlen(header), 0);

    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        send(sockfd, buffer, bytes_read, 0);
    }

    fclose(file);
}