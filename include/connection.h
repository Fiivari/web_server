#ifndef CONNECTION_H
#define CONNECTION_H

#include <winsock2.h>

void handle_connections(int sockfd);
void send_file(SOCKET sockfd, const char *filename);

#endif /* CONNECTION_H */