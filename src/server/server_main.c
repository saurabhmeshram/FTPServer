/* Implementation for Server Side */
#include "common_head.h"

#define PORT 5000
#define BACKLOG 5
#define IP_ADDR "127.0.0.1"

void process_ls_command(int32_t fd);
void process_pwd_command(int32_t fd);

int32_t main (void)
{
    system("clear");
    int32_t command = -1;
    int32_t sock_fd, new_fd;
    int32_t reuse_addr = 1;
    struct sockaddr_in serv, client;
    socklen_t slen = sizeof(struct sockaddr_in);

    sock_fd = FTP_SOCKET(AF_INET, SOCK_STREAM, 0);
    FTP_SETSOCKOPT(sock_fd, SOL_SOCKET, SO_REUSEADDR, &reuse_addr, sizeof(int32_t));

    FTP_MEMSET(&serv, 0, sizeof(struct sockaddr_in));
    FTP_MEMSET(&client, 0, sizeof(struct sockaddr_in));

    serv.sin_family = AF_INET;
    serv.sin_port = htons(PORT);
    serv.sin_addr.s_addr = inet_addr(IP_ADDR);

    FTP_BIND(sock_fd, (const struct sockaddr *) &serv, sizeof(struct sockaddr_in));
    FTP_LISTEN(sock_fd, BACKLOG);
    new_fd = FTP_ACCEPT(sock_fd, (struct sockaddr *) &client, &slen);
    
    while(TRUE) 		/* Loop for Recving Commands */
    {
	read(new_fd, &command, sizeof(int32_t));
	printf("Recv from Buffer : [%d]\n", command);
	process_recvd_command(command, new_fd);
    }

    FTP_CLOSE(sock_fd);
    FTP_CLOSE(new_fd);
    return 0;
}

int process_recvd_command(int command, int fd)
{
    printf("Recivecd Command [%d] from Client\n", command);
    switch(command)
    {
	case FTP_CMD_LS:
	    process_ls_command(fd);
	    break;		
	case FTP_CMD_PWD:
	    process_pwd_command(fd);
	    break;
	default:
	    printf("Unknown Command Recvd\n");
    }
    return 0;
}

void process_pwd_command(int32_t fd)
{
    ENTER;
    int32_t writeb = -1;
    FILE *fp = NULL;
    int8_t *ptr = FTP_MALLOC (sizeof(int8_t) * SIZE);

    fp = FTP_POPEN("pwd", "r");
    fgets(ptr, SIZE, fp); 

    /* Send Result to Client */
    writeb = FTP_WRITE(fd, ptr, FTP_STRLEN(ptr));

    /* Clean-up */
    FTP_FREE(ptr);
    FTP_PCLOSE(fp);
    EXIT;
    return;
}

void process_ls_command(int32_t fd)
{
    ENTER;
    int32_t writeb = -1;
    FILE *fp = NULL;
    int8_t *tmp, *ptr = FTP_MALLOC (sizeof(int8_t) * 2 * SIZE);
    int8_t *sub_ptr = FTP_MALLOC (sizeof(int8_t) * SIZE);

    tmp = ptr;
    fp = FTP_POPEN("ls -l REPO", "r");

    /* Since fgets() breaks at the occurance of new line or EOF, for reading multi-line
       we read, line by line and append it to a common buffer which is finally sent (write) */

    while(fgets(sub_ptr, SIZE, fp) != NULL) 
    {
	FTP_MEMCPY(ptr, sub_ptr, FTP_STRLEN(sub_ptr));
	ptr = ptr + FTP_STRLEN(sub_ptr);
    }

    ptr = tmp;

    /* Send Result to Client */
    writeb = FTP_WRITE(fd, ptr, FTP_STRLEN(ptr));

    /* Clean-up */
    FTP_FREE(sub_ptr);
    FTP_FREE(ptr);
    FTP_PCLOSE(fp);
    EXIT;
    return;
}
