ENABLE_DEBUG = y

CC= gcc
RM= rm
MV= mv
MAKE= make

FTP_PATH:= $(shell pwd)
DATE:= $(shell date)

TARGET_SERVER = server
TARGET_CLIENT = client

CFLAGS := -Wall

ifeq ($(strip $(ENABLE_DEBUG)), y)
CFLAGS += -g
endif

.PHONY: all clean

all:
	$(MAKE) -C $(FTP_PATH)/src/

export CC RM MV MAKE CFLAGS FTP_PATH TARGET_SERVER TARGET_CLIENT
