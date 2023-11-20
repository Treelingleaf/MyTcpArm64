#--------------------------------------------------------------------------------------#
# 配置头文件路径
include_path := $(shell pwd)/inc

# 配置源文件路径
source_path := 

# 指定编译器的前缀
CROSS_COMPILE = # arm-buildroot-linux-gnueabihf-

# 顶层目录的编译选项，用于所有文件
CFLAGS := -Wall -O2 -g

#--------------------------------------------------------------------------------------#
AS		= $(CROSS_COMPILE)as
LD		= $(CROSS_COMPILE)ld
CC		= $(CROSS_COMPILE)gcc
CPP		= $(CC) -E
AR		= $(CROSS_COMPILE)ar
NM		= $(CROSS_COMPILE)nm

STRIP		= $(CROSS_COMPILE)strip
OBJCOPY		= $(CROSS_COMPILE)objcopy
OBJDUMP		= $(CROSS_COMPILE)objdump

export AS LD CC CPP AR NM
export STRIP OBJCOPY OBJDUMP


# 编译时使用指定头文件路径选项
CFLAGS += $(foreach path, $(include_path), -I$(path))

# 指定库，如果有的话
LDFLAGS := $(shell pwd)/lib/libMyTcpArm64.a

export CFLAGS LDFLAGS

TOPDIR := $(shell pwd)
export TOPDIR

# 输出程序
TARGET := myapp

# 指定参加编译的文件或者目录
obj-y += $(patsubst %.c,%.o,$(wildcard *.c))
# 列出顶层目录要排除编译的文件
exclude-files := 
# # 从obj-y中移除要排除的文件
obj-y := $(filter-out $(patsubst %.c,%.o,$(exclude-files)),$(obj-y))
obj-y += $(source_path)



all : start_recursive_build $(TARGET)
	@echo $(TARGET) has been built!

start_recursive_build:
	make -C ./ -f $(TOPDIR)/Makefile.build

$(TARGET) : start_recursive_build
	$(CC) -o $(TARGET) built-in.o $(LDFLAGS)

clean:
	rm -f $(shell find -name "*.o")
	rm -f $(TARGET)

distclean:
	rm -f $(shell find -name "*.o")
	rm -f $(shell find -name "*.d")
	rm -f $(TARGET)

run : all
	@clear
	@./$(TARGET)
