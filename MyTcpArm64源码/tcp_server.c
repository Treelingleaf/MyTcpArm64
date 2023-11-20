// tcp_server.c

#include "MyTcpArm64.h"

int tcp_server_create(const char *bind_address, int port)
{
    // 创建服务器套接字
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1)
    {
        perror("创建服务器套接字失败");
        exit(EXIT_FAILURE);
    }

    // 设置服务器地址结构
    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(bind_address);
    server_address.sin_port = htons(port);

    // 将套接字与地址绑定
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
    {
        perror("绑定服务器套接字失败");
        exit(EXIT_FAILURE);
    }

    // 监听连接
    if (listen(server_socket, 10) == -1)
    {
        perror("监听连接失败");
        exit(EXIT_FAILURE);
    }

    printf("服务器监听在 %s:%d\n", bind_address, port);

    return server_socket;
}

int tcp_server_accept(int server_socket)
{
    // 接受客户端连接
    struct sockaddr_in client_address;
    socklen_t client_address_len = sizeof(client_address);

    int client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_len);
    if (client_socket == -1)
    {
        perror("接受连接失败");
        exit(EXIT_FAILURE);
    }

    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(client_address.sin_addr), client_ip, INET_ADDRSTRLEN);
    printf("接受来自 %s:%d 的连接\n", client_ip, ntohs(client_address.sin_port));

    return client_socket;
}

ssize_t tcp_server_receive(int client_socket, char *buffer, size_t buffer_size)
{
    // 接收数据
    ssize_t bytes_received = recv(client_socket, buffer, buffer_size, 0);
    if (bytes_received == -1)
    {
        perror("接收数据失败");
        exit(EXIT_FAILURE);
    }

    return bytes_received;
}

ssize_t tcp_server_send(int client_socket, const char *data, size_t data_size)
{
    // 发送数据
    ssize_t bytes_sent = send(client_socket, data, data_size, 0);
    if (bytes_sent == -1)
    {
        perror("发送数据失败");
        exit(EXIT_FAILURE);
    }

    return bytes_sent;
}

void tcp_server_close(int server_socket)
{
    // 关闭套接字
    close(server_socket);
    printf("服务器套接字已关闭\n");
}

int tcp_client_connect(const char *server_address, int port)
{
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1)
    {
        perror("创建客户端套接字失败");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(server_address);
    server_addr.sin_port = htons(port);

    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("连接服务器失败");
        exit(EXIT_FAILURE);
    }

    printf("已连接到服务器\n");

    return client_socket;
}

void tcp_client_close(int client_socket)
{
    close(client_socket);
    printf("客户端套接字已关闭\n");
}

ssize_t tcp_send_packet(int socket, const Packet *packet)
{
    // 发送数据包头部
    ssize_t header_size = send(socket, packet, offsetof(Packet, data), 0);
    if (header_size == -1)
    {
        perror("发送数据包头部失败");
        exit(EXIT_FAILURE);
    }

    // 发送实际数据
    ssize_t data_size = send(socket, packet->data, packet->data_size, 0);
    if (data_size == -1)
    {
        perror("发送实际数据失败");
        exit(EXIT_FAILURE);
    }

    return header_size + data_size;
}

ssize_t tcp_receive_packet(int socket, Packet *packet)
{
    // 接收数据包头部
    ssize_t header_size = recv(socket, packet, offsetof(Packet, data), 0);
    if (header_size == -1)
    {
        perror("接收数据包头部失败");
        exit(EXIT_FAILURE);
    }

    // 接收实际数据
    packet->data = (uint8_t *)malloc(packet->data_size);
    if (packet->data == NULL)
    {
        perror("动态分配内存失败");
        exit(EXIT_FAILURE);
    }

    ssize_t data_size = recv(socket, packet->data, packet->data_size, 0);
    if (data_size == -1)
    {
        perror("接收实际数据失败");
        free(packet->data);
        exit(EXIT_FAILURE);
    }

    return header_size + data_size;
}