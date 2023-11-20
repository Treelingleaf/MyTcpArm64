// packet.c

#include "MyTcpArm64.h"

void save_data_to_file(const char *data, size_t data_size, const char *folder_name, const char *file_extension);

void create_directory(const char *dir_name);

Packet create_packet(PacketType type, uint8_t flag, const uint8_t *data, size_t data_size)
{
    Packet packet;
    packet.type = type;
    packet.flag = flag;
    packet.data_size = data_size;

    // 使用指针动态分配内存
    packet.data = (uint8_t *)malloc(data_size);
    if (packet.data == NULL)
    {
        perror("动态分配内存失败");
        exit(EXIT_FAILURE);
    }

    // 复制二进制数据到数据包中
    memcpy(packet.data, data, data_size);

    return packet;
}

void free_packet(Packet *packet)
{
    free(packet->data);
    packet->data = NULL;
    packet->data_size = 0;
}

void parse_received_packet(Packet *received_packet)
{
    switch (received_packet->type)
    {
    case NOTIFICATION:
        printf("接收到通知消息，标志：%u，数据大小：%zu\n", received_packet->flag, received_packet->data_size);
        printf("消息内容: %s\n", received_packet->data);
        break;

    case IMAGE:
        printf("接收到图片数据，标志：%u，数据大小：%zu\n", received_packet->flag, received_packet->data_size);
        // 在这里处理图片数据，received_packet->data 包含实际的图片二进制数据
        // 将图片保存到当前目录下的 Image 目录里，图片以当前时间命名
        save_data_to_file((const char *)received_packet->data, received_packet->data_size, "Image", ".jpg");
        break;

    case FILE_DATA:
        printf("接收到文件数据，标志：%u，数据大小：%zu\n", received_packet->flag, received_packet->data_size);
        // 在这里处理文件数据，received_packet->data 包含实际的文件二进制数据
        // 将文件保存到当前目录下的 File 目录里，以当前时间命名
        save_data_to_file((const char *)received_packet->data, received_packet->data_size, "File", ".dat");
        break;

    default:
        // 预留其他消息类型的处理
        printf("未知类型的数据包，标志：%u，数据大小：%zu\n", received_packet->flag, received_packet->data_size);
        break;
    }
    free_packet(received_packet);
#if DEBUG == 1
    printf("Debug:释放处理完的数据包内存\n");
#endif
}

void save_data_to_file(const char *data, size_t data_size, const char *folder_name, const char *file_extension)
{
    create_directory(folder_name);

    time_t current_time;
    struct tm *time_info;
    char time_buffer[80];

    time(&current_time);
    time_info = localtime(&current_time);

    strftime(time_buffer, sizeof(time_buffer), "%Y%m%d%H%M%S", time_info);

    char file_name[100];
    sprintf(file_name, "./%s/%s%s", folder_name, time_buffer, file_extension);

    FILE *file = fopen(file_name, "wb");
    if (file == NULL)
    {
        perror("无法创建文件");
        exit(EXIT_FAILURE);
    }

    fwrite(data, sizeof(char), data_size, file);

    fclose(file);
    printf("数据已保存到文件：%s\n", file_name);
}

void create_directory(const char *dir_name)
{
    struct stat st = {0};
    if (stat(dir_name, &st) == -1)
    {
        mkdir(dir_name, 0700);
    }
}

void send_notification(int connect_socket, const char *message)
{
    Packet notification_packet = create_packet(NOTIFICATION, 1, (const uint8_t *)message, strlen(message) + 1);
    tcp_send_packet(connect_socket, &notification_packet);
    free_packet(&notification_packet);
}

void send_image(int connect_socket, const char *image_path)
{
    FILE *image_file = fopen(image_path, "rb");
    if (image_file == NULL)
    {
        perror("无法打开图片文件");
        return;
    }

    fseek(image_file, 0, SEEK_END);
    size_t image_size = ftell(image_file);
    fseek(image_file, 0, SEEK_SET);

    uint8_t *image_data = (uint8_t *)malloc(image_size);
    if (image_data == NULL)
    {
        perror("内存分配失败");
        fclose(image_file);
        return;
    }

    size_t bytes_read = fread(image_data, sizeof(uint8_t), image_size, image_file);
    if (bytes_read != image_size)
    {
        perror("读取文件失败");
        fclose(image_file);
        free(image_data);
        exit(EXIT_FAILURE);
    }
    fclose(image_file);

    Packet image_packet = create_packet(IMAGE, 2, image_data, image_size);
    tcp_send_packet(connect_socket, &image_packet);
    free_packet(&image_packet);
    free(image_data);
}

void send_file(int connect_socket, const char *file_path)
{
    FILE *file = fopen(file_path, "rb");
    if (file == NULL)
    {
        perror("无法打开文件");
        return;
    }

    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    uint8_t *file_data = (uint8_t *)malloc(file_size);
    if (file_data == NULL)
    {
        perror("内存分配失败");
        fclose(file);
        return;
    }

    size_t bytes_read = fread(file_data, sizeof(uint8_t), file_size, file);
    if (bytes_read != file_size)
    {
        perror("读取文件失败");
        fclose(file);
        free(file_data);
        exit(EXIT_FAILURE);
    }
    fclose(file);

    Packet file_packet = create_packet(FILE_DATA, 3, file_data, file_size);
    tcp_send_packet(connect_socket, &file_packet);
    free_packet(&file_packet);
    free(file_data);
}