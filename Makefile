CC= gcc
MAKE = make

FTP_SRC:= $(shell pwd)
DATE:= $(shell date)

.PHONY: clean

all:
	@echo "$(DATE)"
	@echo "Building Source Code\n"
	server client

server:
	@echo "This is the Server"

client:
	@echo "This is the Client"
