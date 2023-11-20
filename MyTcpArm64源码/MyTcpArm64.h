#ifndef __MYTCPARM64_H__
#define __MYTCPARM64_H__

#include <stdint.h>
#include <stddef.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define DEBUG 0

typedef enum
{
    NOTIFICATION,
    IMAGE,
    FILE_DATA,
    // 可以添加其他数据类型
} PacketType;

typedef struct
{
    PacketType type;
    size_t data_size;
    uint8_t *data; // 使用指针动态分配内存
    uint8_t flag;
} Packet;

// 创建数据包和释放数据包
Packet create_packet(PacketType type, uint8_t flag, const uint8_t *data, size_t data_size);
void free_packet(Packet *packet); // 添加 const 修饰符

// 解析接受的数据包
void parse_received_packet(Packet *received_packet);

// 发送不同数据类型的数据包
void send_notification(int connect_socket, const char *message);
void send_image(int connect_socket, const char *image_path);
void send_file(int connect_socket, const char *file_path);

// 服务器的创建、接收连接、关闭服务器
int tcp_server_create(const char *bind_address, int port);
int tcp_server_accept(int server_socket);
void tcp_server_close(int server_socket);

// 客户端连接服务器和关闭连接
int tcp_client_connect(const char *server_address, int port);
void tcp_client_close(int client_socket);

// 数据包的收发，双端通用
ssize_t tcp_receive_packet(int socket, Packet *packet);
ssize_t tcp_send_packet(int socket, const Packet *packet);

#endif