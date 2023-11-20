// tcp_server.h

#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stddef.h>
#include <stdint.h>
#include <errno.h>
#include "packet.h"

int tcp_server_create(const char *bind_address, int port);
int tcp_server_accept(int server_socket);
ssize_t tcp_server_receive(int client_socket, char *buffer, size_t buffer_size);
ssize_t tcp_server_send(int client_socket, const char *data, size_t data_size);
void tcp_server_close(int server_socket);

int tcp_client_connect(const char *server_address, int port);
void tcp_client_close(int client_socket);

ssize_t tcp_receive_packet(int socket, Packet *packet);
ssize_t tcp_send_packet(int socket, const Packet *packet);

#endif // TCP_SERVER_H
