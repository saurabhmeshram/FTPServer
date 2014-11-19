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

/* Path where all the FTP files are Stored */
#define FTP_REPO "./REPO/"

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

const char *command_str[] = {
	"CD"
	"GET"
	"HELP"
	"LS"
	"PUT"
	"PWD"
	"QUIT"
};


#define FILENAMESIZE 	64
#define FILEDATASIZE 	2048

typedef struct filestr
{
	int file_size;
	char file_name[FILENAMESIZE];
	char file_data[FILEDATASIZE];
}filestr_t;


/* FTP Wrapper Functions */
#define FTP_SOCKET	socket
#define FTP_BIND	bind 	
#define FTP_LISTEN	listen
#define FTP_ACCEPT	accept
#define FTP_CONNECT	connect
#define FTP_SETSOCKOPT	setsockopt

#define FTP_OPEN	open
#define FTP_CLOSE	close
#define FTP_POPEN	popen
#define FTP_PCLOSE	pclose
#define FTP_READ	read
#define FTP_WRITE	write

#define FTP_MALLOC	malloc
#define FTP_FREE	free
#define FTP_MEMSET	memset
#define FTP_MEMCPY	memcpy

#define FTP_STRLEN	strlen
#define FTP_STRCPY	strcpy
#define FTP_STRNCPY	strncpy
#define FTP_STRCMP	strcmp
#define FTP_STRNCMP	strncmp
#define FTP_STRTOK	strtok

#define FTP_FSCANF	fscanf
#define FTP_FTELL	ftell
#define FTP_FSEEK	fseek
#define FTP_REWIND	rewind
#define FTP_FOPEN	fopen
#define FTP_FCLOSE	fclose
#define FTP_FREAD	fread
#define FTP_FWRITE	fwrite

/* Misc Macros */
#define _LINE 	__LINE__
#define _FILE	__FILE__
#define _FUNC 	__func__
#define ENTER 	printf("Entered Function [%s][%d]\n", _FUNC, _LINE)
#define EXIT  	printf("Exiting Function [%s][%d]\n", _FUNC, _LINE)
#define DEBUG  	printf("Here in [%s][%d]\n", _FUNC, _LINE)

#define SIZE64 		64
#define SIZE128 	128
#define SIZE512 	512
#define SIZE1024 	1024
#define SIZE 		1024
#define TRUE 	1
#define FALSE 	0

/* Standard Declarations */

#ifdef __cplusplus
}
#endif
#endif 		/* For __COMMON_HEAD_H_*/
