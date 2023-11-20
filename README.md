# MyTcpArm64

MyTcpArm64 是一个用于处理 TCP 连接的 C 语言库，旨在简化 TCP 服务器和客户端的创建和数据交互过程。

## 功能特点

- 封装了常见的 TCP 服务器和客户端函数，简化网络编程。
- 提供了一个灵活的数据包格式，支持发送不同类型的数据。
- 示例代码演示了如何使用该库进行通知消息、图片传输和文件传输。

## 数据包格式

MyTcpArm64 使用自定义的数据包格式来进行不同类型的数据传输。每个数据包包含以下信息：

- **类型（PacketType）：** 表示数据的类型，可以是通知消息、图片或文件数据等。
- **标志（Flag）：** 一个预留的标志，用于表示特定的信息或操作。
- **数据大小（Data Size）：** 实际数据的大小。
- **数据（Data）：** 存储实际数据的字节数组。

### 数据包类型

MyTcpArm64 支持以下数据包类型：

1. **通知消息（NOTIFICATION）：** 用于传输文本消息，例如通知、提示等。
2. **图片数据（IMAGE）：** 用于传输图片二进制数据。
3. **文件数据（FILE_DATA）：** 用于传输文件二进制数据。

## 如何使用

### 示例

以下是一个数据包的示例：

```plaintext
Type: NOTIFICATION
Flag: 1
Data Size: 16
Data: "Hello, world!"


### 编译

在项目根目录下执行以下命令：

```bash
make
```

### 示例

#### 服务器端

```bash
./server
```

#### 客户端

```bash
./client
```

## 示例代码

请查看 `main.c` 文件以获取关于如何使用库的示例代码。

## 贡献

欢迎贡献代码和提出问题！请查看 [贡献指南](CONTRIBUTING.md) 获取更多信息。

## 授权许可

该项目采用 MIT 许可证 - 详情请参阅 [LICENSE](LICENSE) 文件。

```

你可以根据项目的实际情况进行调整。确保在 README 中提供足够的信息，使其他人能够理解项目的目的、如何构建和运行它，以及如何参与贡献。
