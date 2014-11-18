#include "common_head.h"

int32_t init_connection(struct sockaddr_in *client, int8_t **arr);
int32_t stop_connection(int32_t fd);
int32_t process_command(int8_t *cmd, int sock_fd);
int32_t put_file_command(int32_t fd ,int8_t *cmd);
void pwd_command(int32_t fd);
void list_files_command(int32_t fd);

/* 
Description: Init a Connection to the FTP Server.
Return: Socket FD of the client 
 */
int32_t init_connection(struct sockaddr_in *client, int8_t **arr)
{
    /* Create Socket for Client */
    int32_t sock_fd = -1;
    sock_fd = FTP_SOCKET(AF_INET, SOCK_STREAM, 0);
    printf("Created Socket, Sock_fd is [%d]\n", sock_fd);

    FTP_MEMSET(client, 0, sizeof(struct sockaddr_in));

    client->sin_family = AF_INET;
    client->sin_addr.s_addr = inet_addr(arr[1]);
    client->sin_port = htons(atoi(arr[2]));

    printf("Connecting...\n");
    FTP_CONNECT(sock_fd, (struct sockaddr *)client, sizeof(struct sockaddr_in));
    return sock_fd;
}

int32_t stop_connection(int32_t fd)
{
    FTP_CLOSE(fd);
    return TRUE;
}

int32_t main(int32_t argc, char **argv)
{
    system("clear");
    if (1 == argc) {
	printf("Usage : <%s> <IP_ADDRESS> <PORT>\n", argv[0]);
	exit(EXIT_FAILURE);
    }
    int32_t sock_fd = -1;
    struct sockaddr_in client;
    int8_t quit = 1;
    int32_t c = -1;

    int8_t *command = FTP_MALLOC (64 * sizeof(uint8_t));

    sock_fd = init_connection(&client, argv);
    printf("Recvd Sockfd as [%d]\n", sock_fd);


    do {
	printf("ftp-bash:$ ");
	fgets(command, 64, stdin);
	command[FTP_STRLEN(command) - 1] = '\0';

	/* Do Nothing if input is new line */
	if (command[0] == 10) {
	    printf("Newline");
	    break;
	}
	/* To-do: Add Function to remove spaces */
	// command = remove_spaces(command);

	else {
	    if(-1 == process_command(command, sock_fd))
		quit = 0;
	}
    } while(1 == quit);

    FTP_FREE(command);
    stop_connection(sock_fd);
    return 0;
}

int32_t process_command(int8_t *cmd, int sock_fd)
{
    if (0 == FTP_STRCMP(cmd, "quit"))
    {	
	printf("Recieved Quit Command\n");
	return -1;
    }
    else if (0 == FTP_STRCMP(cmd, "pwd"))
	pwd_command(sock_fd);	
    else if (0 == FTP_STRNCMP((const char *) cmd, "put", strlen("put")))
	put_file_command(sock_fd, cmd);
    else if (0 == FTP_STRCMP((const char *) cmd, "ls"))
	list_files_command(sock_fd);
    return 0;
}

/* Description : List all the files available on the Server */
void list_files_command(int fd)
{
    int32_t readb = -1;
    int8_t *buff = FTP_MALLOC(SIZE * sizeof(int8_t) * 2);
    FTP_MEMSET(buff, 0, (SIZE * 2 * sizeof(int8_t)));

    printf("Printing Files available on Server \n");
    int32_t c = FTP_CMD_LS;

    FTP_WRITE(fd, &c, sizeof(c));

    readb = FTP_READ(fd, buff, SIZE * 2);
    printf("%s\n", buff);
    FTP_FREE(buff);
    return;	
}

/* Description : Get current working Directory in Server */
void pwd_command(int32_t fd)
{
    int32_t readb = -1;
    int8_t *buff = FTP_MALLOC(SIZE * sizeof(int8_t));
    FTP_MEMSET(buff, 0, (SIZE * sizeof(int8_t)));

    printf("PWD on Server: ");
    int32_t c = FTP_CMD_PWD;

    FTP_WRITE(fd, &c, sizeof(c));

    readb = FTP_READ(fd, buff, SIZE);
    printf("%s\n", buff);
    FTP_FREE(buff);
    return;	
}

#if 1
/* Description: Put (upload) a file into the FTP server */
int32_t put_file_command(int32_t fd, int8_t *cmd)
{
	int32_t i, j = 0, size;
	FILE *fp = NULL;
	int8_t *ptr = NULL, *send_buf = NULL;
	int8_t **file_names = NULL;

	file_names = (int8_t **) FTP_MALLOC(sizeof(int8_t *));
	for(i=0; i<10; i++)				/* Max of ten files of max strlen 64 each */
		*(file_names + i) = FTP_MALLOC(sizeof(int8_t) * 64);

	printf("CMD : [%s]\n", cmd);
	/* Tokenise the file names */
	ptr = FTP_STRTOK(cmd, " ");
	printf("First Token  : [%s]\n", ptr);
	do {
		printf("\tToken  : [%s]\n", ptr);
		FTP_MEMCPY(*(file_names + j), ptr, strlen(ptr));
		printf("\tFile Name : [%s]\n", *(file_names + j));
		j++;
	}while (ptr = (FTP_STRTOK(NULL, " ")));

	printf("Files to transfer:\n");
	for(i=0; i<j; i++)
		printf("\t[%s]\n", *(file_names + i));

	/* To-do : Check if file exist */

	/* Read the file content into buffer */
	printf("fopen failed for file [%s]\n", *(file_names+1));
	if(NULL == (fp = FTP_FOPEN( *(file_names+1), "r"))) {
	printf("fopen failed for file [%s]\n", *(file_names+1));
	return -1;
	}

	FTP_FSEEK(fp, 0, SEEK_END);
	size = FTP_FTELL(fp);
	FTP_REWIND(fp);
	
	send_buf = FTP_MALLOC(sizeof(uint8_t) * (size + 1));
	FTP_FREAD(send_buf, sizeof(uint8_t), size, fp);

	printf("Content of File\n%s\n", send_buf);

	/* Write File buffer to the Server */
	//printf("File names : [%s]\n", ptr);
	return 0;
}
#endif
