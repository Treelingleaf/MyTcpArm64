EXTRA_CFLAGS := -D DEBUG
obj-y += $(patsubst %.c,%.o,$(wildcard *.c))

# 列出要排除的文件
exclude-files := 

# # 从obj-y中移除要排除的文件
obj-y := $(filter-out $(patsubst %.c,%.o,$(exclude-files)),$(obj-y))
