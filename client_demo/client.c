// client_main.c

#include "MyTcpArm64.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    // 服务器的IP和监听端口
    const char *server_address = "127.0.0.1";
    int port = 8080;
    ssize_t bytes_received;

    int connect_socket = tcp_client_connect(server_address, port);
    while (1)
    {
        // 定义接收数据包
        Packet received_packet;
        // 发送的通知消息缓冲区
        char message[1024];
        printf("请输入要发送的消息:");
        scanf("%s", message);
        send_notification(connect_socket, message);
        // 接收来自服务器的反馈
        bytes_received = tcp_receive_packet(connect_socket, &received_packet);
        parse_received_packet(&received_packet);
    }

    /*
    *示例 1: 发送通知消息
    send_notification(connect_socket, "这是一条消息！");
    bytes_received = tcp_receive_packet(connect_socket, &received_packet);
    parse_received_packet(&received_packet);

    *示例 2: 发送图片数据--调用send_image接口
    send_image(connect_socket, "./1.jpg");
    bytes_received = tcp_receive_packet(connect_socket, &received_packet);
    parse_received_packet(&received_packet);

    *示例 3: 发送文件数据
    send_file(connect_socket, "./file.txt");
    bytes_received = tcp_receive_packet(connect_socket, &received_packet);
    parse_received_packet(&received_packet);

    *如果有其他类型数据，请在MyTcpArm64.h自定义并重新编译库
    */
    // // 关闭服务器套接字
    // // tcp_client_close(connect_socket);

    return 0;
}
