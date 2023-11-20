CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LIBS = -lm

# List of source files
SRCS = tcp_server.c packet.c

# List of header files
HDRS = tcp_server.h packet.h

# Object files
OBJS = $(SRCS:.c=.o)

# Name of the library
LIB_NAME = libMyTcpArm64.a

# Target for building the library
$(LIB_NAME): $(OBJS)
	ar rcs $(LIB_NAME) $(OBJS)

# Target for building the object files
%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

# Target for cleaning up the build
clean:
	rm -f $(OBJS) $(LIB_NAME)

.PHONY: clean
