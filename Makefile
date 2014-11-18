ENABLE_DEBUG = y

# Makefile Variables # 
CC= gcc
RM= rm
MV= mv
MAKE= make

FTP_PATH:= $(shell pwd)
DATE:= $(shell date)

TARGET_SERVER = server_process
TARGET_CLIENT = client_process

CFLAGS := 

ifeq ($(strip $(ENABLE_DEBUG)), y)
CFLAGS += -g
endif

.PHONY: all
.SILENT: all

all:	
	@echo "\n$(DATE)"
	@echo "Building Source..\n"
	$(MAKE) -C $(FTP_PATH)/src/

clean:
	@echo "\n\nRemoving Binaries and Object files..\n"
	$(MAKE) -C $(FTP_PATH)/src/ clean
	@echo "Done.\n"


export CC RM MV MAKE CFLAGS FTP_PATH TARGET_SERVER TARGET_CLIENT
