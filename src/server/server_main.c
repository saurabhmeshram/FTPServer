/* Implementation for Server Side */
#include "common_head.h"

#define PORT 5000
#define BACKLOG 5
#define IP_ADDR "172.16.7.110"

int32_t main (void)
{
    int32_t sock_fd, new_fd;
    struct sockaddr_in serv, client;
    sock_fd = FTP_SOCKET(AF_INET, SOCK_STREAM, 0);

    FTP_MEMSET(&serv, 0, sizeof(struct sockaddr_in));
    FTP_MEMSET(&client, 0, sizeof(struct sockaddr_in));

    serv.sin_family = AF_INET;
    serv.sin_port = htons(PORT);
    serv.sin_addr.s_addr = inet_addr(IP_ADDR);

    if (-1 == FTP_BIND(sock_fd, (const struct sockaddr *) &serv, sizeof(struct sockaddr_in)))
    {
	printf("Error at bind\n");
	exit(EXIT_FAILURE);
    }

    if (-1 == FTP_LISTEN(sock_fd, BACKLOG))
	printf("Error at listen\n");

    socklen_t slen = sizeof(struct sockaddr_in);

    printf("Accepting...\n");
    if (-1 == (new_fd = FTP_ACCEPT(sock_fd, (struct sockaddr *) &client, &slen)))
    {
	printf("Error at Accept\nErrorNo:[%d]\tErrorMsg:[%s]\n", errno, strerror(errno));
	exit(EXIT_FAILURE);
    }

    int32_t command_t = -1;
    while(TRUE)
    {
	read(new_fd, &command_t, sizeof(command_t));
	printf("Recv from Buffer : [%d]\n", command_t);
    }

    return 0;
}
