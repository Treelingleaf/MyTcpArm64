// packet.h

#ifndef PACKET_H
#define PACKET_H

#include <stdint.h>
#include <stddef.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>

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

Packet create_packet(PacketType type, uint8_t flag, const uint8_t *data, size_t data_size);
void free_packet(Packet *packet); // 添加 const 修饰符

// 处理接受的数据包
void parse_received_packet(Packet *received_packet);

// 顶层封装
void send_notification(int connect_socket, const char *message);
void send_image(int connect_socket, const char *image_path);
void send_file(int connect_socket, const char *file_path);

#endif // PACKET_H
