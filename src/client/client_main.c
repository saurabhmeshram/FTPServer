#include "common_head.h"

int32_t init_connection(struct sockaddr_in *client, int8_t **arr);
int32_t stop_connection(int32_t fd);
int32_t process_command(int8_t *cmd);
int32_t put_file_command(int8_t *cmd);

/* Description: Init a Connection to the FTP Server.
Return: Socket FD of the client */
int32_t init_connection(struct sockaddr_in *client, int8_t **arr)
{
    /* Create Socket for Client */
    int32_t sock_fd = -1;
    sock_fd = FTP_SOCKET(AF_INET, SOCK_STREAM, 0);
    printf("Created Socket, Sock_fd is [%d]\n", sock_fd);

    memset(client, 0, sizeof(struct sockaddr_in));

    client->sin_family = AF_INET;
    client->sin_addr.s_addr = inet_addr(arr[1]);
    client->sin_port = htons(atoi(arr[2]));

    printf("Connecting...\n");
    if (-1 == FTP_CONNECT(sock_fd, (struct sockaddr *)client, sizeof(struct sockaddr_in)))
    {
	printf("Error at Connect\nErrorNo:[%d]\tErrorMsg:[%s]\n", errno, strerror(errno));
	exit(EXIT_FAILURE);
    }	
    return sock_fd;
}

int32_t stop_connection(int32_t fd)
{
    FTP_CLOSE(fd);
    return TRUE;
}

int32_t main(int32_t argc, char **argv)
{
    if (1 == argc) {
	printf("Usage : <%s> <IP_ADDRESS> <PORT>\n", argv[0]);
	exit(EXIT_FAILURE);
    }
    int32_t sock_fd = -1;
    struct sockaddr_in client;

    int8_t quit = 1;

    int8_t *command = NULL;
    command = FTP_MALLOC (64 * sizeof(uint8_t));

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
	    if(-1 == process_command(command))
		quit = 0;
	}
    } while(1 == quit);

    FTP_FREE(command);
    stop_connection(sock_fd);
    return 0;
}

int32_t process_command(int8_t *cmd)
{
    if (0 == FTP_STRCMP(cmd, "quit"))
    {	
	printf("Recieved Quit Command\n");
	return -1;
    }
    else if (0 == FTP_STRNCMP((const char *) cmd, "put", strlen("put")))
    {
	printf("Transferring file to FTP Server\n");
	put_file_command(cmd);

    }
    //else
    //printf("Unknown Command\nType \"help\" for more information.\n");
    return 0;
}

int32_t put_file_command(int8_t *cmd)
{
    return 0;
}
