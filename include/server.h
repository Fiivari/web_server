#ifndef SERVER_H
#define SERVER_H

#include <winsock2.h>

int create_and_bind_socket();
void handle_connections(int sockfd);

#endif /* SERVER_H */