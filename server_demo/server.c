// main.c

#include "MyTcpArm64.h"

int main()
{
    const char *bind_address = "127.0.0.1";
    int port = 8080;

    int connect_socket = tcp_server_create(bind_address, port);
    int client_socket = tcp_server_accept(connect_socket);
    while (1)
    {
        // 接收数据包
        Packet received_packet;
        ssize_t bytes_received = tcp_receive_packet(client_socket, &received_packet);
        if (bytes_received == 0)
        {
            // 客户端连接已经断开，关闭客户端套接字并退出循环
            printf("客户端连接已断开\n");
            tcp_server_close(client_socket);
            break;
        }
        else if (bytes_received < 0)
        {
            // 处理接收数据包失败的情况
            perror("接收数据包失败");
            break;
        }

        parse_received_packet(&received_packet);
        send_notification(client_socket, "接收成功！\n");
    }

    // 关闭服务器套接字
    tcp_server_close(connect_socket);

    return 0;
}