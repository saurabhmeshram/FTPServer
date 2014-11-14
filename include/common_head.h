#ifndef __COMMON_HEAD_H_
#define __COMMON_HEAD_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Common Header Files */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

/* Socket related files */
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

/* FTP Macros */
#define FTP_SOCKET	socket
#define FTP_BIND	bind 	
#define FTP_LISTEN	listen
#define FTP_ACCEPT	accept
#define FTP_CONNECT	connect

#define FTP_OPEN	open
#define FTP_CLOSE	close
#define FTP_READ	read
#define FTP_WRITE	write
#define FTP_RECV	recv
#define FTP_SEND	send

#define FTP_MALLOC	malloc
#define FTP_FREE	free
#define FTP_MEMSET	memset
#define FTP_MEMCPY	memcpy

#define FTP_STRLEN	strlen
#define FTP_STRCPY	strcpy
#define FTP_STRCMP	strcmp
#define FTP_STRNCMP	strncmp

/* Misc Macros */
#define _LINE 	__LINE__
#define _FILE	__FILE__
#define _FUNC 	__func__
#define ENTER 	printf("Entered Function [%s][%d]\n", _FUNC, _LINE)
#define EXIT  	printf("Exiting Function [%s][%d]\n", _FUNC, _LINE)

#define TRUE 	1
#define FALSE 	0

/* Path where all the FTP files are Stored */
#define FTP_REPO "./../repo/"

/* Enum contains the Commands to send */
enum command {
	FTP_CMD_CD = 0,
	FTP_CMD_GET,
	FTP_CMD_HELP,
	FTP_CMD_LS,
	FTP_CMD_PUT,
	FTP_CMD_PWD,
	FTP_CMD_QUIT = -1,
}command_t;

/* Standard Declarations */



#ifdef __cplusplus
}
#endif
#endif 		/* For __COMMON_HEAD_H_*/
