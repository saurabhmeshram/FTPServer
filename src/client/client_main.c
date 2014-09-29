#include "common_head.h"

#define IP_ADDR "127.0.0.1" 
#define PORT  4000

int main (void)
{
	printf("Connecting...");
	char buffer[20] = {0};
	int sock_fd;
	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	
	printf("Connecting...");
	struct sockaddr_in serv;
        memset(&serv, 0, sizeof(struct sockaddr_in));
        serv.sin_family = AF_INET;
        serv.sin_port = PORT;
        serv.sin_addr.s_addr = inet_addr(IP_ADDR);

	printf("Connecting...");
	connect (sock_fd, &serv, sizeof(struct sockaddr_in));

	while (1)
	{
		sprintf(buffer, "%s", "Hello World\n");
		write(sock_fd, &buffer, sizeof(buffer));
		memset(buffer, 0, sizeof(buffer));
	}
	return 0;
}
